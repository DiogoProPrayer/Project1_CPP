
#include <iostream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

namespace svg
{
    // Function declaration - definition later in the code
    void readElements(XMLElement *root, XMLElement *elem,vector<SVGElement *>& svg_elements, vector<string> transformations = {});



    void readSVG(const string& svg_file, Point& dimensions, vector<SVGElement *>& svg_elements)
    {
        XMLDocument doc;
        XMLError r = doc.LoadFile(svg_file.c_str());
        if (r != XML_SUCCESS)
        {
            throw runtime_error("Unable to load " + svg_file);
        }
        XMLElement *xml_elem = doc.RootElement();

        dimensions.x = xml_elem->IntAttribute("width");
        dimensions.y = xml_elem->IntAttribute("height");
        
        readElements(xml_elem, doc.RootElement(),svg_elements); 
    }

    void readElements(XMLElement *root, XMLElement *elem,vector<SVGElement *>& svg_elements, vector<string> transformations = {}){
        

        if (elem->Name()=="ellipse"){
            //Define an Ellipse
            Point p = {elem->IntAttribute("cx"), elem->IntAttribute("cy")};
            Point radius = {elem->IntAttribute("rx"), elem->IntAttribute("ry")};
            Ellipse objeto(parse_color(elem->Attribute("fill")), p, radius);

            //Check if any transformation is applied, and transform if needed
            if (elem->Attribute("transform")!=0)
            {
                if (elem->Attribute("transform-origin")!=0)
                {
                    objeto.transform(elem->Attribute("transform"),elem->Attribute("transform-origin"));
                } else{
                    objeto.transform(elem->Attribute("transform"));
                }
            }

            //Apply group transformations (to be done)

        }
        else if (elem->Name()=="circle"){
            //Define a Circle
            Point p = {elem->IntAttribute("cx"), elem->IntAttribute("cy")};
            Circle objeto(parse_color(elem->Attribute("fill")), p, elem->IntAttribute("r"));

            //Check if any transformation is applied, and transform if needed
            if (elem->Attribute("transform")!=0)
            {
                if (elem->Attribute("transform-origin")!=0)
                {
                    objeto.transform(elem->Attribute("transform"),elem->Attribute("transform-origin"));
                } else{
                    objeto.transform(elem->Attribute("transform"));
                }
            }

            //Apply group transformations (to be done)


        }
        else if (elem->Name()=="rect")
        {
            //Define a Rectangle
            Point p = {elem->IntAttribute("x"), elem->IntAttribute("y")};
            Rectangle objeto(parse_color(string(elem->Attribute("fill"))), elem->IntAttribute("height"), elem->IntAttribute("width"), p);

            //Check if any transformation is applied, and transform if needed
            if (elem->Attribute("transform")!=0)
            {
                if (elem->Attribute("transform-origin")!=0)
                {
                    objeto.transform(elem->Attribute("transform"),elem->Attribute("transform-origin"));
                } else{
                    objeto.transform(elem->Attribute("transform"));
                }
            }

            //Apply group transformations (to be done)

        }
         else if (elem->Name()=="polyline")
        {
            //Define a Polyline
            string points = elem->Attribute("points");
            points += ' ';
            vector <Point> cluster = {};
            Point ponto = {};
            string cache = "";
            for(char c: points){
                if (c==',')
                {
                    ponto.x = stoi(cache);
                    cache = "";
                } else if ((c==' ') && (cache!=""))
                {
                    ponto.y = stoi(cache);
                    cache = "";
                    cluster.push_back(ponto);
                    ponto.x = 0;
                    ponto.y = 0;
                } else if ((c>='0')&&(c<='9'))
                {
                    cache.push_back(c);
                }
            }
            Polyline objeto(parse_color(elem->Attribute("stroke")), cluster);
            

            //Check if any transformation is applied, and transform if needed
            if (elem->Attribute("transform")!=0)
            {
                if (elem->Attribute("transform-origin")!=0)
                {
                    objeto.transform(elem->Attribute("transform"),elem->Attribute("transform-origin"));
                } else{
                    objeto.transform(elem->Attribute("transform"));
                }
            }

            //Apply group transformations (to be done)

        }else if (elem->Name()=="line")
        {
            //Define a Line
            Point start = {elem->IntAttribute("x1"),elem->IntAttribute("y1")};
            Point end = {elem->IntAttribute("x2"),elem->IntAttribute("y2")};
            Line objeto(parse_color(elem->Attribute("stroke")), start, end);
            

            //Check if any transformation is applied, and transform if needed
            if (elem->Attribute("transform")!=0)
            {
                if (elem->Attribute("transform-origin")!=0)
                {
                    objeto.transform(elem->Attribute("transform"),elem->Attribute("transform-origin"));
                } else{
                    objeto.transform(elem->Attribute("transform"));
                }
            }

            //Apply group transformations (to be done)

        }  else if (elem->Name()=="polygon")
        {
            //Define a Polygon
            string points = elem->Attribute("points");
            points += ' ';
            vector <Point> poly = {};
            Point ponto = {};
            string cache = "";
            for(char c: points){
                if (c==',')
                {
                    ponto.x = stoi(cache);
                    cache = "";
                } else if ((c==' ') && (cache!=""))
                {
                    ponto.y = stoi(cache);
                    cache = "";
                    poly.push_back(ponto);
                    ponto.x = 0;
                    ponto.y = 0;
                } else if ((c>='0')&&(c<='9'))
                {
                    cache.push_back(c);
                }
            }
            Polygon objeto(parse_color(elem->Attribute("fill")), poly);
            

            //Check if any transformation is applied, and transform if needed
            if (elem->Attribute("transform")!=0)
            {
                if (elem->Attribute("transform-origin")!=0)
                {
                    objeto.transform(elem->Attribute("transform"),elem->Attribute("transform-origin"));
                } else{
                    objeto.transform(elem->Attribute("transform"));
                }
            }

            //Apply group transformations (to be done)

        }
        






        for (XMLElement *child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
    {
        readElements(root, child, svg_elements, transformations);   
    }


    }


}