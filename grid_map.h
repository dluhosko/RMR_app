#ifndef GRID_MAP_H
#define GRID_MAP_H

#include "definitions.h"
#include <math.h>
#include <exception>
#include <iostream>

namespace grid_map {

    const static int UNKNOWN = -1;
    const static int OCCUPIED = 1;
    const static int EMPTY = 0;


    class MapException : public std::exception {
    public:

        MapException(std::string str) : err(str) {

        }

        virtual ~MapException() throw() {}
        virtual const char *what() const throw() {
            return ("Map exception: " + err).c_str();
        }

    private:
        std::string err;
    };

    class Map {
    public:

        Map(double width, double height, double resolution) {

            this->resolution = resolution;

            this->height = round(height / resolution);
            this->width = round(width / resolution);

            printf("\nheight %d width %d\n\n", this->height, this->width);
           // this->height = height;
            //this->width = width;

            map.resize(this->width * this->height, EMPTY);
        }

        int getValue(double x, double y) {

            int i = getRow(y);
            int j = getColumn(x);

            checkCoorditanes(i,j);
           return map[i*width + j];
        }

        int getValue(int i, int j) {

            checkCoorditanes(i,j);
            return map[i*width + j];
        }

        int getValue(int id) {

            if (id >= map.size())
                throw MapException("id is out of map");

            return map[id];
        }

        void setValue(double x, double y, int value) {

            int i = getRow(y);
            int j = getColumn(x);

            checkCoorditanes(i,j);
            printf("set value double");
            map[i*width + j] = value;
        }

        void setValue(int i, int j, int value) {
            printf("set value int");

            checkCoorditanes(i,j);

            map[i*width + j] = value;
        }

        void setValue(int id, int value) {

            if (id >= map.size())
                throw MapException("id is out of map");

            map[id] = value;
        }

        void setLine(Definitions::POINT p1, Definitions::POINT p2){

            double angle = Definitions::getAngle(p2, p1);
            double dist = Definitions::getDistance(p2, p1);

            printf("\ndist %f angle %f\n\n", dist, angle);
            double increment = 0;
            while (increment <= dist) {
                double x = p1.x + increment * cos(angle);
                double y = p1.y + increment * sin(angle);
                printf("x %f, y %f\n", x,y);
                setValue(x, y, grid_map::OCCUPIED);
                increment += resolution;
            }
        }

        void setPolygon(std::vector<Definitions::POINT> points){

            for (int i = 1; i < points.size(); i++){
                setLine(points[i - 1], points[i]);
            }
            setLine(points[points.size() -1], points[0] );
        }
        //ok
        int getRow(double y){

            int i = height/ 2.0 + y / resolution;
            if (i < 0  || i > height)  throw MapException("i: " +std::to_string(i) + "  point is out of map, height of map is " + std::to_string(height));
            return i;
        }
        //ok
        int getColumn(double x){

            int j = width / 2.0 + x / resolution;
            if( j < 0 || j >= width) throw MapException("j: " +std::to_string(j) + " point is out of map, width of map is " + std::to_string(width));
            return j;
        }
        //ok
        int getRowById(int id){

            if (id >= map.size())
                throw MapException("id is out of map");
            return id/width;
        }
        //ok
        int getColumnById(int id){

            if (id >= map.size())
                throw MapException("id is out of map");
            return id%width;
        }

        //x = i*r - h*r/2 + r/2
        //ok
        double getX(int j){

            if( j < 0 || j >= width) throw MapException("j: " +std::to_string(j) + " point is out of map, width of map is " + std::to_string(width));
            return resolution*(j - width/2.0 + 0.5);
        }
        //ok
        double getY(int i){

            if (i < 0  || i > height)  throw MapException("i: " +std::to_string(i) + "  point is out of map, height of map is " + std::to_string(height));
            return resolution*(i - height/2.0 + 0.5);
        }

        int getCellId(Definitions::POINT p){

            int id = getColumn(p.y) * width + getRow(p.x);
            if (id >= map.size())
                throw MapException("id is out of map");

            return id;
        }
        //ok
        int getCellId(int i, int j){

            checkCoorditanes(i,j);
            return i * width + j;
        }

        Definitions::POINT operator () (int i, int j){

           checkCoorditanes(i,j);
            return {getX(j), getY(i)};
        }

        Definitions::POINT operator () (int id){

            if (id >= map.size())
                throw MapException("id is out of map");
            return {getX(getColumnById(id)), getY(getRowById(id))};
        }

        int size(){ return map.size(); }

        int getHeight() {return height; }

        int getWidth() {return width; }

        std::vector<std::vector<float> > getGraph(){

            std::vector<std::vector<float> > graph;

            float distance = resolution;
            float diagDistance = sqrt(2)*resolution;

            graph.resize(map.size());
            for (int i = 0; i < map.size(); i++) {
                graph[i].resize(map.size(), 0);
            }

            for (int i = 0; i < graph.size() - 1; i++){

                //ak je obsadena, tak preskoc
                if (map[i] == OCCUPIED)
                    continue;

                //skontroluj bunku, ktora je na pravo ale nie mimo mapy (vpravo)
                if ((i+1) % width){

                    if (map[i + 1] != OCCUPIED){
                        graph[i][i + 1] = distance;
                        graph[i + 1][i] = distance;
                    }
                }

                //skontroluj bunky pod bunkou
               if (i / width < height - 1){

                   //skontroluj bunku, ktora je na pravo ale nie mimo mapy (diagonalne v pravo)
                    if ( (i + 1) % width)

                        if (map[i + width + 1] != OCCUPIED){
                            graph[i][i + width + 1] = diagDistance;
                            graph[i + width + 1][i] = diagDistance;
                        }

                   //skontroluj bunku, ktora je na lavo ale nie mimo mapy (diagonalne vlavo)
                   if ( i % width)

                        if (map[i + width - 1] != OCCUPIED){
                            graph[i][i + width - 1] = diagDistance;
                            graph[i + width - 1][i] = diagDistance;
                        }

                   //skontroluj bunku, ktora je kolmo dole
                    if (map[i + width] != OCCUPIED){
                        graph[i][i + width] = distance;
                        graph[i + width][i] = distance;
                    }
                }
            }
            return graph;
        }

    private:
        double resolution;
        int height;
        std::vector<int> map;
        int width;

        void checkCoorditanes(int i, int j){

            printf("i %d height %d, j %d, width %d\n", i, height, j, width);
            if (i < 0  || i > height)  throw MapException("i: " +std::to_string(i) + "  point is out of map, height of map is " + std::to_string(height));
            if( j < 0 || j >= width) throw MapException("j: " +std::to_string(j) + " point is out of map, width of map is " + std::to_string(width));

        }
    };
}



#endif // GRID_MAP_H
