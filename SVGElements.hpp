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
        virtual void transform(std::string trans,Point) =0;
    };

    // Declaration of namespace functions
    void readSVG(const std::string &svg_file,Point &dimensions,std::vector<SVGElement *> &svg_elements);
    void convert(const std::string &svg_file,const std::string &png_file);
    
    
   
    class Ellipse : public SVGElement{
    public:
        //! Constructor of an Ellipse.
        //! @param fill Ellipse color.
        //! @param center Ellipse center.
        //! @param radius Ellipse radius in x and y axes.
        Ellipse(const Color &fill,const Point &center,const Point &radius);
        
        //! Executes the draw function.
        //! @param img Png where the image will be drawn. 
        void draw(PNGImage &img) const override;

            
        //! Executes the transformation.
        //! @param trans transformation to be done.
        //! @param cent transformation-origin.
        void transform(std::string trans, Point cent)  override;


    protected:

        Color fill;
        Point center;
        Point radius;
    };



    class Circle:public Ellipse{
    public:
        //! Constructor of a Circle.
        //! @param fill circle  color.
        //! @param center circle center.
        //! @param center radius of the circle in the x and y axis. 
        Circle(const Color &fill, const Point &center, const Point &radius);
    };

    class Polyline: public SVGElement{
    public:
        //! Constructor of a polyline.
        //! @param stroke color of the line.
        //! @param clusterpoint points belonging to the polyline.
        Polyline(const Color &stroke,std::vector<Point> &clusterpoints);

        //! Executes the draw function.
        //! @param img Png where the image will be drawn.
        void draw(PNGImage &img) const override;

        //! Executes the transformation.
        //! @param trans transformation to be done.
        //! @param cent transformation-origin.
        void transform(std::string trans, Point cent)  override;

    protected:
        Color stroke;
        std::vector<Point> clusterpoints;
    };

    class Line:public Polyline{
    public:
        //! Constructor of a line.
        //! @param stroke color of the line.
        //! @param Start beginning point.
        //! @param End end point.
        Line(const Color &stroke,Point End,Point Start,std::vector<Point> clusterpoints={});
    private:
        Point End;
        Point Start;
    };

    class Polygon: public SVGElement{
    public:
        //! Constructor of a polygon.
        //! @param fill color of the polygon.
        //! @param poly points defining the polygon.
        Polygon(const Color &fill,std::vector<Point> &poly);

        //! Executes the draw function.
        //! @param img Png where the image will be drawn.
        void draw(PNGImage&img) const override;
        
        //! Executes the transformation.
        //! @param trans transformation to be done.
        //! @param cent transformation-origin.
        void transform(std::string trans, Point cent)  override;


    protected:
        Color fill;
        std::vector<Point> poly;
    };
    
    class Rectangle:public Polygon{
    public:
        //! Constructor of a Rectangle.
        //! @param fill rectangle color.
        //! @param width rectangle width.
        //! @param upleftcor upper left corner of the rectangle. 
        Rectangle(const Color &fill,const int &height,const int &width, const Point &upleftcor,std::vector<Point> clusterpoints={});
        
    private:
        int height;
        int width;
        Point upleftcor;
    };
    

}
#endif
