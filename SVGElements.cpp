#include "SVGElements.hpp"
#include <sstream>
#include <iostream>
namespace svg
{
    // These must be defined!
    SVGElement::SVGElement() {

    }
    SVGElement::~SVGElement() {

    }

    // Ellipse (initial code provided)
    Ellipse::Ellipse(const Color &fill,const Point &center,const Point &radius): fill(fill), center(center), radius(radius) {}

    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, radius, fill);
    }

    void Ellipse::transform(std::string trans,Point cent) {
        std:: string par;
        int val1;
        for(char &i:trans){
            if(i==','||i=='(' || i==')'){
                i=' ';
            }
        }
        std:: istringstream inp(trans);
        inp>>par;
        if(par=="rotate"){
            inp>>val1;
            center=center.rotate(cent, val1);
        }
        else if(par=="scale"){
            inp>>val1;
            center=center.scale(cent,val1);
            radius.x=radius.x*val1;
            radius.y=radius.y*val1;

           
        }
        else if(par=="translate"){
            Point t;
            inp>>t.x;
            inp>>t.y;
            center=center.translate(t);
        
            
        }
    }



    Circle::Circle(const Color &fill, const Point &center, const Point &radius) : Ellipse(fill, center, radius){}

    Rectangle::Rectangle(const Color &fill,const int &height,const int &width, const Point &upleftcor,std::vector<Point> clusterpoints) : Polygon(fill,poly),height(height),width(width),upleftcor(upleftcor){
        Point uprightcor;
        Point dleftcor;
        Point drightcor;
        uprightcor.x=upleftcor.x+width-1;
        uprightcor.y=upleftcor.y;
        drightcor.x=uprightcor.x;
        drightcor.y=uprightcor.y+height-1;
        dleftcor.x=upleftcor.x;
        dleftcor.y=drightcor.y;
        Polygon::poly.push_back(upleftcor);
        poly.push_back(uprightcor);
        poly.push_back(drightcor);
        poly.push_back(dleftcor);
    }

    Polyline::Polyline( const Color &stroke, std::vector<Point> &clusterpoints):stroke(stroke),clusterpoints(clusterpoints){}
    void Polyline:: draw(PNGImage &img)const{
        int size=clusterpoints.size();
        for(int i=1;i<size;i++){
        img.draw_line(clusterpoints[i-1],clusterpoints[i],stroke);
        }

    }
    void Polyline::transform(std::string trans,Point cent) {
        std:: string par;
        int val1;
          for(char &i:trans){
            if(i==','||i=='(' || i==')'){
                i=' ';
            }
        }
        std:: istringstream inp(trans);
        inp>>par;
        if(par=="rotate"){
            inp>>val1;
            for(Point &i:clusterpoints){
                i=i.rotate(cent,val1);
            }


        }
        else if(par=="scale"){
            inp>>val1;
            for(Point &i:clusterpoints){
                i=i.scale(cent,val1);
            }
           
        }
        else if(par=="translate"){
            Point t;
            inp>>t.x;
            inp>>t.y;
            for(Point &i:clusterpoints){
                i=i.translate(t);
            } 
        }
    }

    Line::Line(const Color &stroke,Point End, Point Start,std::vector<Point> clusterpoints): Polyline(stroke,clusterpoints),End(End),Start(Start){
    this->clusterpoints.push_back(Start);
    this->clusterpoints.push_back(End);
    }

    


    Polygon:: Polygon(const Color &fill,std::vector<Point> &poly):fill(fill),poly(poly){}
    void Polygon::draw(PNGImage &img) const
    {   
        img.draw_polygon(poly,fill);
    }
    void Polygon::transform(std::string trans,Point cent) {
        std:: string par;
        int val1;
          for(char &i:trans){
            if(i==','||i=='(' || i==')'){
                i=' ';
            }
        }
        std:: istringstream inp(trans);
        inp>>par;
        if(par=="rotate"){
            inp>>val1;
            for(Point &i:poly){
                i=i.rotate(cent,val1);
            }
        }
        else if(par=="scale"){
            inp>>val1;
            for(Point &i:poly){
                i=i.scale(cent,val1);
            }

           
        }
        else if(par=="translate"){
            Point t;
            inp>>t.x;
            inp>>t.y;
            for(Point &i:poly){
                i=i.translate(t);
            }
        }
    }

}


