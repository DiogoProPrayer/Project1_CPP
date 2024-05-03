//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"

namespace svg
{
    class SVGElement
    {

    public:
        SVGElement();
        virtual ~SVGElement();
        virtual void draw(PNGImage &img) const = 0;
    };

    // Declaration of namespace functions
    // readSVG -> implement it in readSVG.cpp
    // convert -> already given (DO NOT CHANGE) in convert.cpp

    void readSVG(const std::string &svg_file,
                 Point &dimensions,
                 std::vector<SVGElement *> &svg_elements);
    void convert(const std::string &svg_file,
                 const std::string &png_file);

    class Ellipse : public SVGElement
    {
    public:
        Ellipse(const Color &fill, const Point &center, const Point &radius);
        void draw(PNGImage &img) const override;

    private:
        Color fill;
        Point center;
        Point radius;
    };
    //Circle is a exception of an Ellipse. Thereafter Circle is a subclass of Ellipse will use the same draw fucntion later
    
    class Circle:public SVGElement{
    public:
        Circle(const Color &fill, const Point &center, const Point &radius);
        void draw(PNGImage &img) const override;
    private:
        Color fill;
        Point center;
        int radius;
    };

    class Rectangle:public SVGElement{
    public:
        Rectangle(const Color &fill,const int &height,const int &width, const Point &upleftcor);
        void draw(PNGImage &img) const override;
    private:
    Color fill;
        int height;
        int width;
        Point upleftcor;
    };

    class Polyline: public SVGElement{
    public:
        Polyline(const Color &stroke,const std::vector<Point> &clusterpoints);
        void draw(PNGImage &img) const override;
    private:
        Color stroke;
        std::vector<Point> clusterpoints;
    };

    class Line:public SVGElement
    {
    public:
        Line(const Color &stroke,const  Point &Start,const Point &End);
        void draw(PNGImage &img) const override;
    private:
        Color stroke;
        Point Start;
        Point End;
    };

    class Polygon: public SVGElement{
    public:
        Polygon(const Color &fill,const std::vector<Point> &poly);
        void draw(PNGImage&img) const override;
    private:
        Color fill;
        std::vector<Point> poly;
    };

   

}
#endif

