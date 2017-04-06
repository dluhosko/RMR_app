#include "mainwindow.h"
#include "ui_mainwindow.h"


std::vector<Definitions::POINT> points;

int counter;

iRobotCreate *robot;
rplidar *lidar;
Navigation *nav;
grid_map::Map *map;
//GlobalPlanner *gPlanner;


 void *mappingThread(void *param);


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

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


    //ParamsThread *params=(ParamsThread*)malloc(sizeof(ParamsThread));
    //params->classpointer=this;
    //params->param=param;
   // params->functionPointer=(void *)callback;

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
   static double x = 0;
   static double y = 0;
   static double fi = 0;

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


       //
  
    //DEBUG info
    //printf("\n x: %f, y : %f, fi: %f\n",x,y,fi*RAD2DEG);

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

    start.x = 0;
    start.y = 0;

    grid_map::Map map(50,50,0.1);
    GlobalPlanner gPlanner(&map);
    gPlanner.makePlan( start, target, &points);

    for (int i = 0; i < points.size(); i++)
        printf("%d. x %f, y %f", points[i].x, points[i].y);


}
void MainWindow::on_turnButton_clicked(){

  //  delete map;
   map = new grid_map::Map(5,5,0.1);

   // int nic;
    threadLidarMapping = pthread_create(&threadHandleLidar,NULL,mappingThread,NULL);

}


void *mappingThread(void *param){

  //  Mapping mapping((Mapping *) param);
    Mapping mapping(map);

    while (true){

        printf("trheade\n");

    LaserMeasurement measure = lidar->getMeasurement();

         for(int i=0; i<measure.numberOfScans;i++)
         {
             char helptext[200];
            // sprintf(helptext,"%f %f",measure.Data[i].scanAngle,measure.Data[i].scanDistance);
             //ui->textEdit->append(helptext);

         }
     }
}

