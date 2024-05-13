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
    {   std::cout<<"center : "<<center.x<<","<<center.y<<std::endl;

        img.draw_ellipse(center, radius, fill);
    }

    void Ellipse::transform(std::string trans,Point cent) {
        std:: string par;
        int val1;
        for(char &i:trans){
            if(trans[i]==','||trans[i]=='(' || trans[i]==')'){
                trans[i]=' ';
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
            center=center.scale(center,val1);
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



    Circle::Circle(const Color &fill, const Point &center, const int &radius):fill(fill),center(center),radius(radius){}
    void Circle:: draw(PNGImage &img)const{
        Point radiusasP;
        radiusasP.x=radiusasP.y=radius;
        img.draw_ellipse(center,radiusasP,fill);
    }
    void Circle::transform( std::string trans,Point cent) {
        std:: string par;
        int val1;
        int val2;
        for(char &i:trans){
            if(trans[i]==','||trans[i]=='(' || trans[i]==')'){
                trans[i]=' ';
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
            center=center.scale(center,val1);
            radius=radius*val1;

           
        }
        else if(par=="translate"){
            Point t;
            inp>>t.x;
            inp>>t.y;
            center=center.translate(t);
        }
    }

    Rectangle::Rectangle(const Color &fill,const int &height,const int &width, const Point &upleftcor):fill(fill),height(height),width(width),upleftcor(upleftcor){
        this->height-=1;
        this->width-=1;
        Point uprightcor;
        Point dleftcor;
        Point drightcor;
        uprightcor.x=upleftcor.x+width;
        uprightcor.y=upleftcor.y;
        drightcor.x=uprightcor.x;
        drightcor.y=uprightcor.y+height;
        dleftcor.x=upleftcor.x;
        dleftcor.y=drightcor.y;
        clusterpoints.push_back(upleftcor);
        clusterpoints.push_back(uprightcor);
        clusterpoints.push_back(drightcor);
        clusterpoints.push_back(dleftcor);
    }
    void Rectangle::draw(PNGImage &img)const{
        img.draw_polygon(clusterpoints,fill);
    }
    void Rectangle::transform(std::string trans,Point cent) {
        std:: string par;
        int val1;
        int val2;
        for(char &i:trans){
            if(trans[i]==','||trans[i]=='(' || trans[i]==')'){
                trans[i]=' ';
            }
        }
        std:: istringstream inp(trans);
        inp>>par;
        if(par=="rotate"){
            inp>>val1;
            for(Point &i:clusterpoints){
                i=i.rotate(i,val1);
            }

        }
        else if(par=="scale"){
            inp>>val1;
            for(Point)
           
        }
        else if(par=="translate"){
         inp>>val1;
         inp>>val2;
        }
    }

    Polyline::Polyline(const Color &stroke,const std::vector<Point> &clusterpoints):stroke(stroke),clusterpoints(clusterpoints){}
    void Polyline:: draw(PNGImage &img)const{
        int size=clusterpoints.size();
        for(int i=1;i<size;i++){
            std::cout<<"ok"<<std::endl;
            img.draw_line(clusterpoints[i-1],clusterpoints[i],stroke);
        }
    }
    void Polyline::transform(std::string trans,Point cent) {
        std:: string par;
        int val1;
        int val2;
        for(char &i:trans){
            if(trans[i]==','||trans[i]=='(' || trans[i]==')'){
                trans[i]=' ';
            }
        }
        
        val1=0;
        std:: istringstream inp(trans);
        inp>>par;
        if(par=="rotate"){
            inp>>val1;


        }
        else if(par=="scale"){
         inp>>val1;
           
        }
        else if(par=="translate"){
         inp>>val1;
         inp>>val2;
        }
    }

    Line::Line(const Color &stroke,const  Point &Start,const Point &End):stroke(stroke),Start(Start),End(End){}
    void Line::draw(PNGImage &img) const{
        img.draw_line(Start,End,stroke);
    }
    void Line::transform(std::string trans,Point cent) {
        std:: string par;
        int val1;
        int val2;
        for(char &i:trans){
            if(trans[i]==','||trans[i]=='(' || trans[i]==')'){
                trans[i]=' ';
            }
        }
        
        val1=0;
        std:: istringstream inp(trans);
        inp>>par;
        if(par=="rotate"){
            inp>>val1;


        }
        else if(par=="scale"){
         inp>>val1;
           
        }
        else if(par=="translate"){
         inp>>val1;
         inp>>val2;
        }
    }


    Polygon:: Polygon(const Color &fill,const std::vector<Point> &poly):fill(fill),poly(poly){}
    void Polygon::draw(PNGImage &img) const
    {
        img.draw_polygon(poly,fill);
    }
    void Polygon::transform(std::string trans,Point cent) {
        std:: string par;
        int val1;
        int val2;
        for(char &i:trans){
            if(trans[i]==','||trans[i]=='(' || trans[i]==')'){
                trans[i]=' ';
            }
        }
        
        val1=0;
        std:: istringstream inp(trans);
        inp>>par;
        if(par=="rotate"){
            inp>>val1;


        }
        else if(par=="scale"){
         inp>>val1;
           
        }
        else if(par=="translate"){
         inp>>val1;
         inp>>val2;
        }
    }

}
