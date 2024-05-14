//! @file shape.hpp
#ifndef __svg_SVGElements_hpp__
#define __svg_SVGElements_hpp__

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"
#include <vector>

namespace svg
{
    class SVGElement
    {

    public:
        SVGElement();
        virtual ~SVGElement();
        virtual void draw(PNGImage &img) const = 0;
        virtual void transform(std::string trans,Point cent={0,0}) =0;
    };

    // Declaration of namespace functions
    // readSVG -> implement it in readSVG.cpp
    // convert -> already given (DO NOT CHANGE) in convert.cpp

    void readSVG(const std::string &svg_file,Point &dimensions,std::vector<SVGElement *> &svg_elements);
    void convert(const std::string &svg_file,const std::string &png_file);
    
    
   
    class Ellipse : public SVGElement
    {
    public:
        //! Constructor of an Ellipse.
        //! Takes the radius as a Point, as well as the center and uses this values to draw an Ellipse.which is then filled with the color defined in fill.
        //! @param fill Ellipse color.
        //! @param center Ellipse center.
        //! @param radius Ellipse radius in x and y axes.
        Ellipse(const Color &fill, const Point &center, const Point &radius);

        //! Executes the draw function.
        //! @param img Png.
        void draw(PNGImage &img) const override;

        //!

        void transform(std::string trans, Point cent)  override;


    private:

        Color fill;
        Point center;
        Point radius;
    };



    class Circle:public SVGElement{
    public:
        //! Constructor of a Circle.
        //! Recieves a fill element.
        //! @param fill circle  color.
        //! @param center circle center.
        //! @param center radius of the circle in the x and y axis. 
        Circle(const Color &fill, const Point &center, Point &radius);

        //! Executes the draw function.
        //! @param img Png where the image will be drawn. 
        void draw(PNGImage &img) const override;

        void transform(std::string trans, Point cent)  override;

    private:

        Color fill;
        Point center;
        Point radius;
    };

    class Rectangle:public SVGElement{
    public:
        //! Constructor of a Rectangle.
        //! Recieves a fill elemen.
        //! @param fill rectangle color.
        //! @param width rectangle width.
        //! @param upleftcor upper left corner of the rectangle. 
        Rectangle(const Color &fill,const int &height,const int &width, const Point &upleftcor);
        
        //! Executes the draw function.
        //! @param img Png where the image will be drawn.
        void draw(PNGImage &img) const override;



         void transform(std::string trans, Point cent)  override;
    private:

        Color fill;
        int height;
        int width;
        Point upleftcor;
        std::vector<Point>clusterpoints;
    };

    class Polyline: public SVGElement{
    public:
        //! Constructor of a polyline.
        //! @param stroke color of the line.
        //! @param clusterpoint points belonging to the polyline.
        Polyline(const Color &stroke,const std::vector<Point> &clusterpoints);

        //! Executes the draw function.
        //! @param img Png where the image will be drawn.
        void draw(PNGImage &img) const override;


         void transform(std::string trans, Point cent)  override;
    private:
        Color stroke;
        std::vector<Point> clusterpoints;
    };

    class Line:public SVGElement
    {
    public:
        //! Constructor of a line.
        //! @param stroke color of the line.
        //! @param Start beginning point.
        //! @param End end point.
        Line(const Color &stroke,const  Point &Start,const Point &End);

        //! Executes the draw function.
        //! @param img Png where the image will be drawn.
        void draw(PNGImage &img) const override;


        void transform(std::string trans, Point cent)  override;

    private:
        Color stroke;
        Point Start;
        Point End;
    };

    class Polygon: public SVGElement{
    public:
        //! Constructor of a polygon.
        //! @param fill color of the polygon.
        //! @param poly points defining the polygon.
        Polygon(const Color &fill,const std::vector<Point> &poly);

        //! Executes the draw function.
        //! @param img Png where the image will be drawn.
        void draw(PNGImage&img) const override;



         void transform(std::string trans, Point cent)  override;


    private:
        Color fill;
        std::vector<Point> poly;
    };

   

}
#endif



