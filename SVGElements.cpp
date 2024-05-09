#include "SVGElements.hpp"

#include "SVGElements.hpp"

namespace svg
{
    // These must be defined!
    SVGElement::SVGElement() {}
    SVGElement::~SVGElement() {}

    // Ellipse (initial code provided)
    Ellipse::Ellipse(const Color &fill,const Point &center,const Point &radius): fill(fill), center(center), radius(radius) {}

    void Ellipse::draw(PNGImage &img) const
    {   
        img.draw_ellipse(center, radius, fill);
    }
    // @todo provide the implementation of SVGElement derived classes
    // HERE -->


    Circle::Circle(const Color &fill, const Point &center, const int &radius):fill(fill),center(center),radius(radius) {}
    void Circle:: draw(PNGImage &img)const{
        Point radiusasP;
        radiusasP.x=radiusasP.y=radius;
        img.draw_ellipse(center,radiusasP,fill);
    }

    Rectangle::Rectangle(const Color &fill,const int &height,const int &width, const Point &upleftcor):fill(fill),height(height),width(width){}
    void Rectangle::draw(PNGImage &img)const{
        Point uprightcor;
        Point dleftcor;
        Point drightcor;
        std::vector<Point> tp;
        uprightcor.x=upleftcor.x+width;
        uprightcor.y=upleftcor.y;
        drightcor.x=uprightcor.x;
        drightcor.y=uprightcor.y+height;
        dleftcor.x=upleftcor.x;
        dleftcor.y=upleftcor.y+height;
        tp.push_back(upleftcor);
        tp.push_back(uprightcor);
        tp.push_back(drightcor);
        tp.push_back(dleftcor);
        img.draw_polygon(tp,fill);
    }

    Polyline::Polyline(const Color &stroke,const std::vector<Point> &clusterpoints):stroke(stroke),clusterpoints(clusterpoints){}
    void Polyline:: draw(PNGImage &img)const{
        int size=clusterpoints.size();
        for(int i=1;i<size;i++){
            img.draw_line(clusterpoints[i-1],clusterpoints[i],stroke);
        }
    }

    Line::Line(const Color &stroke,const  Point &Start,const Point &End):stroke(stroke),Start(Start),End(End){}
    void Line::draw(PNGImage &img) const{
        img.draw_line(Start,End,stroke);
    }

    Polygon:: Polygon(const Color &fill,const std::vector<Point> &poly):fill(fill),poly(poly){}
    void Polygon::draw(PNGImage &img)const{
        img.draw_polygon(poly,fill);
    }

    



}


