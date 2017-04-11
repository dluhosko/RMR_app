#include "mainwindow.h"
#include "ui_mainwindow.h"


std::vector<Definitions::POINT> points;

int counter;

iRobotCreate *robot;
rplidar *lidar;
Navigation *nav;
grid_map::Map *map;
//GlobalPlanner *gPlanner;

double x,y, fi;
pthread_mutex_t odom_mutex;
pthread_mutex_t draw_map_mutex;

void *mappingThread(void *param);


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    x = 0;
    y = 0;
    fi = 0;
    points.clear();

    //create robot
    ui->setupUi(this);
    robot = new iRobotCreate();

    //create main class for navigation
    nav = new Navigation(robot, 0.7, 10);

    //connect lidar
    lidar->connect("/dev/laser");
    lidar->enable();
    lidar->start();


    timer=NULL;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updatePicture()));
    timer->start(500);

    map = new grid_map::Map(5,5,0.1);

    threadLidarMapping = pthread_create(&threadHandleLidar,NULL,mappingThread,NULL);


}

MainWindow::~MainWindow()
{
    delete ui;
}


int MainWindow::demoCallback(CreateSensors inputData,void *ioPointer)
{
    MainWindow *currentWindow=(MainWindow*)ioPointer;
  //  currentWindow->update();
    QString vystup = "Neplatny udaj.";
    QString actualPosition =  "Start";

   //Suradnice
   fi += inputData.Angle*Definitions::DEG2RAD;
   if (fi > 2*M_PI)
	fi -= 2*M_PI;
   if (fi < 0)
	fi += 2*M_PI;

    x += inputData.Distance * cos(fi);
    y += inputData.Distance * sin(fi);


       nav->setPosition(x,y,fi);
       if (counter < points.size()){
        vystup = "ide na ciel" + QString::number(counter) + " x= "+QString::number(points[counter].x)+ " y= "+QString::number(points[counter].y);   //" x= "+QString::number(points[counter].x)
        //printf("\n ziadany smer %f %f\n",points[counter].x, points[counter].y);
            if (nav->goToPoint(points[counter].x,points[counter].y)){
                 //robot->move(0,0);
                 sleep(1);
                 vystup = "v cieli" + QString::number(counter);
                  counter++;
            //sleep(2);
        }

        } else robot->move(0, 0);


    actualPosition = "x=" + QString::number(x) + " y="+ QString::number(y) + " fi="+(QString::number(fi*Definitions::RAD2DEG)) ;
    currentWindow->ui->label2->setText(actualPosition);
    currentWindow->ui->label->setText(vystup);
}

void MainWindow::on_pushButton_clicked()
{
    robot->ConnectToPort("/dev/robot",this);
    connect( this, SIGNAL( showMB() ), this, SLOT( showMessageBox() ), Qt::BlockingQueuedConnection );

    robot->dataProcess(this,&demoCallback);
}

void MainWindow::on_pushButton_2_clicked()
{

   // robot->move(50, -50);

    counter = 0;

    points.clear();
    Definitions::POINT p;
    p.x = 1000;
    p.y = 0;
    points.push_back(p);

    p.x = 1000;
    p.y = 1800;
    points.push_back(p);

/*    p.x = 3300;
    p.y = 1800;
    points.push_back(p);

    p.x = 0;
    p.y = 0;
    points.push_back(p);
*/

   // robot.move(-35,35);
    //usleep(1000*1000);
    robot->move(0,0);
}

void MainWindow::on_pointButton_clicked(){

    counter = 0;
    points.clear();
    Definitions::POINT target;
    Definitions::POINT start;

    QString posX = ui->onX->toPlainText();
    QString posY = ui->onY->toPlainText();
    target.x = posX.toFloat();
    target.y = posY.toFloat();

    start.x = x;
    start.y = y;

    grid_map::Map map(50,50,0.1);
    GlobalPlanner gPlanner(&map);
    if (!gPlanner.makePlan( start, target, &points))
        printf("\n ERROR: NO PATH FOUND\n");
    else printf("plan found: coordinates: \n");

    for (int i = 0; i < points.size(); i++)
        printf("%d. x %f, y %f\n", points[i].x, points[i].y);

}

void MainWindow::on_turnButton_clicked(){

    loadMap();
    paintEventStatus=13;
    update();

}


void *mappingThread(void *param){

  //  Mapping mapping((Mapping *) param);
    Mapping mapping(map);

    while (true) {

        Mapping mapping(map);

        while (true) {

            LaserMeasurement measure = lidar->getMeasurement();

            for (int i = 0; i < measure.numberOfScans; i++) {
                char helptext[200];
                // sprintf(helptext,"%f %f",measure.Data[i].scanAngle,measure.Data[i].scanDistance);
                //ui->textEdit->append(helptext);

            }

            pthread_mutex_lock(&odom_mutex);
            mapping.setPosition(x, y, fi);
            pthread_mutex_unlock(&odom_mutex);

            pthread_mutex_lock(&draw_map_mutex);
            mapping.update(&measure);
            pthread_mutex_unlock(&draw_map_mutex);


        }
    }
}


void MainWindow::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    int resolution = 100;
    int offset_x = 300;
    int offset_y = 300;

    if(paintEventStatus==13)
    {
        painter.setPen(Qt::black);
        painter.setBrush(Qt::white);

        pthread_mutex_lock(&draw_map_mutex);

        for(int i=0;i< map->size();i++)
        {
            Definitions::POINT p = (*map)(i);
            double x1 = (p.x ) * resolution  + offset_x;
            double y1 = (-p.y ) * resolution  + offset_y;
            double x2 = (p.x + 0.1) * resolution  + offset_x;
            double y2 = (-p.y  + 0.1) * resolution  + offset_y;

            if (map->getValue(i) == grid_map::OCCUPIED){
                // printf("\ntest: 1. %f %f\n2.%f %f\n\n", x1, y1,x2,y2 );
                painter.setBrush(Qt::green);
            } else if (map->getValue(i) == grid_map::PATH)
                painter.setBrush(Qt::red);
            else if (map->getValue(i) == grid_map::UNKNOWN)
                painter.setBrush(Qt::gray);
            else
                painter.setBrush(Qt::white);

            painter.drawRect(x1,y1,x2,y2);
        }
        pthread_mutex_unlock(&draw_map_mutex);
    }

    paintEventStatus=0;

    QWidget::paintEvent(event);
}

void MainWindow::updatePicture()
{
    paintEventStatus=13;
    update();
}

bool MainWindow::loadMap() {

    TMapArea mapss;
    map_loader m_loader;
    m_loader.load_map("priestor.txt", mapss);

    double max_y = 0;
    double max_x = 0;

    for (int i = 0; i < mapss.wall.numofpoints; i++) {

        if (mapss.wall.points[i].point.x > max_x)
            max_x = mapss.wall.points[i].point.x;

        if (mapss.wall.points[i].point.y > max_y)
            max_y = mapss.wall.points[i].point.y;

    }

    double width = max_x / 100 ;
    double heigth = max_y / 100;
    double resolution = 0.1;

    if (map != NULL){
        delete map;
        map = NULL;
    }

    map = new grid_map::Map(width + 1, heigth + 1, resolution);
    map->setEmpty();
    /* std::vector<Definitions::POINT> polygon(4);
      polygon[0].x = -2.5;
      polygon[0].y = 0;
      polygon[1].x = 2;
      polygon[1].y = 0;
      polygon[2].x = 2;
      polygon[2].y = 1;
      polygon[3].x = 0;
      polygon[3].y = 1;

      //map->setLine(polygon[0], polygon[1]);
      //map->setPolygon(polygon);*/

    std::vector<Definitions::POINT> polygon(mapss.wall.numofpoints);
    for (int i = 0; i < mapss.wall.numofpoints; i++){
        polygon[i].x = mapss.wall.points[i].point.x / 100 - width/2;
        polygon[i].y = mapss.wall.points[i].point.y / 100 - heigth/2;
    }
    map->setPolygon(polygon);

    for (int i =0; i < mapss.numofObjects; i++){
        polygon.clear();
        polygon.resize(mapss.obstacle[i].numofpoints);
        for (int j = 0; j < mapss.obstacle[i].numofpoints; j++){

            polygon[j].x = mapss.obstacle[i].points[j].point.x / 100 - width/2 ;
            polygon[j].y = mapss.obstacle[i].points[j].point.y / 100 - heigth/2;
        }
        map->setPolygon(polygon);
    }
}

