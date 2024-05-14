
#include <iostream>
#include "SVGElements.hpp"
#include "external/tinyxml2/tinyxml2.h"
#include <sstream>

using namespace std;
using namespace tinyxml2;

namespace svg
{
    // Function declaration - definition later in the code
    void readElements(XMLElement *root, XMLElement *elem,vector<SVGElement *>& svg_elements, vector<pair<string,Point>> &transformations);

    void use(XMLElement *root, XMLElement *elem, string id ,vector<SVGElement *>& svg_elements, vector<pair<string,Point>> &transformations);


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
        
        vector<pair<string,Point>> transformations;
        readElements(xml_elem, doc.RootElement(),svg_elements,transformations); 
    }


    void readElements(XMLElement *root, XMLElement *elem,vector<SVGElement *>& svg_elements, vector<pair<string,Point>> &transformations){
        

        if (string(elem->Name())=="ellipse"){
            //Define an Ellipse
            Point p = {elem->IntAttribute("cx"), elem->IntAttribute("cy")};
            Point radius = {elem->IntAttribute("rx"), elem->IntAttribute("ry")};
            Ellipse* objeto = new Ellipse(parse_color(elem->Attribute("fill")), p, radius);
            //Check if any transformation is applied, and transform if needed
            if (elem->Attribute("transform")!=0)
            {
                if (elem->Attribute("transform-origin")!=0)
                {
                    Point o;
                    string ori = elem->Attribute("transform-origin");
                    for(char &c: ori){
                        if (c==',' ){c=' ';}
                        if (c=='(' ){c=' ';}
                        if (c==')' ){c=' ';}
                    }
                    istringstream cogumelo(ori);
                    cogumelo>>o.x;
                    cogumelo>>o.y;
                    objeto->transform(string(elem->Attribute("transform")), o );
                } else{
                    Point o = {0,0};
                    cout<<"Called Trans without O";
                    objeto->transform(string(elem->Attribute("transform")),o);
                }
            }
            //Apply group transformations
            for (pair<string, Point> trans : transformations){
                objeto->transform(trans.first,trans.second);
            }
            // Push_Back the final object with all transformations applied
            svg_elements.push_back(objeto);
        }



        else if (string(elem->Name())=="circle"){
            //Define a Circle
            Point p = {elem->IntAttribute("cx"), elem->IntAttribute("cy")};
            Point r = {elem->IntAttribute("r"),elem->IntAttribute("r")};
            Circle* objeto = new Circle(parse_color(elem->Attribute("fill")), p, r);
            //Check if any transformation is applied, and transform if needed
            if (elem->Attribute("transform")!=0)
            {
                cout<<"Entrou na condição";
                if (elem->Attribute("transform-origin")!=0)
                {
                    Point o;
                    string ori = elem->Attribute("transform-origin");
                    for(char &c: ori){
                        if (c==',' ){c=' ';}
                        if (c=='(' ){c=' ';}
                        if (c==')' ){c=' ';}
                    }
                    istringstream cogumelo(ori);
                    cogumelo>>o.x;
                    cogumelo>>o.y;
                    cout<<"Called Trans with O\n";
                    objeto->transform(string(elem->Attribute("transform")), o );
                } else{
                    Point o = {0,0};
                    cout<<"Called Trans without O\n";
                    objeto->transform(string(elem->Attribute("transform")),o);
                }
            }
            //Apply group transformations
            for (pair<string, Point> trans : transformations){
                objeto->transform(trans.first,trans.second);
            }
            // Push_Back the final object with all transformations applied
            svg_elements.push_back(objeto);
        }



        else if (string(elem->Name())=="rect")
        {
            //Define a Rectangle
            Point p = {elem->IntAttribute("x"), elem->IntAttribute("y")};
            Rectangle* objeto = new Rectangle(parse_color(string(elem->Attribute("fill"))), elem->IntAttribute("height"), elem->IntAttribute("width"), p);
            //Check if any transformation is applied, and transform if needed
            if (elem->Attribute("transform")!=0)
            {
                if (elem->Attribute("transform-origin")!=0)
                {
                    Point o;
                    string ori = elem->Attribute("transform-origin");
                    for(char &c: ori){
                        if (c==',' ){c=' ';}
                        if (c=='(' ){c=' ';}
                        if (c==')' ){c=' ';}
                    }
                    istringstream cogumelo(ori);
                    cogumelo>>o.x;
                    cogumelo>>o.y;
                    objeto->transform(string(elem->Attribute("transform")), o );
                } else{
                    Point o = {0,0};
                    cout<<"Called Trans without O";
                    objeto->transform(string(elem->Attribute("transform")),o);
                }
            }
            //Apply group transformations
            for (pair<string, Point> trans : transformations){
                objeto->transform(trans.first,trans.second);
            }
            // Push_Back the final object with all transformations applied
            svg_elements.push_back(objeto);
        }



         else if (string(elem->Name())=="polyline")
        {
            //Define a Polyline
            string points = elem->Attribute("points");
            vector <Point> cluster = {};
            Point ponto;
            for(char &c: points){
                if (c==',' ){c=' ';}
            }
            istringstream turf(points);
            while(turf){
                turf>>ponto.x;
                turf>>ponto.y;
                cluster.push_back(ponto);
            }
            Polyline* objeto = new Polyline(parse_color(elem->Attribute("stroke")), cluster);
            //Check if any transformation is applied, and transform if needed
            if (elem->Attribute("transform")!=0)
            {
                if (elem->Attribute("transform-origin")!=0)
                {
                    Point o;
                    string ori = elem->Attribute("transform-origin");
                    for(char &c: ori){
                        if (c==',' ){c=' ';}
                        if (c=='(' ){c=' ';}
                        if (c==')' ){c=' ';}
                    }
                    istringstream cogumelo(ori);
                    cogumelo>>o.x;
                    cogumelo>>o.y;
                    objeto->transform(string(elem->Attribute("transform")), o );
                } else{
                    Point o = {0,0};
                    cout<<"Called Trans without O";
                    objeto->transform(string(elem->Attribute("transform")),o);
                }
            }
            //Apply group transformations
            for (pair<string, Point> trans : transformations){
                objeto->transform(trans.first,trans.second);
            }
            // Push_Back the final object with all transformations applied
            svg_elements.push_back(objeto);
        }
        
        
        
        else if (string(elem->Name())=="line")
        {
            //Define a Line
            Point start = {elem->IntAttribute("x1"),elem->IntAttribute("y1")};
            Point end = {elem->IntAttribute("x2"),elem->IntAttribute("y2")};
            Line *objeto = new Line(parse_color(elem->Attribute("stroke")), start, end);
            //Check if any transformation is applied, and transform if needed
            if (elem->Attribute("transform")!=0)
            {
                if (elem->Attribute("transform-origin")!=0)
                {
                    Point o;
                    string ori = elem->Attribute("transform-origin");
                    for(char &c: ori){
                        if (c==',' ){c=' ';}
                        if (c=='(' ){c=' ';}
                        if (c==')' ){c=' ';}
                    }
                    istringstream cogumelo(ori);
                    cogumelo>>o.x;
                    cogumelo>>o.y;
                    objeto->transform(string(elem->Attribute("transform")), o );
                } else{
                    Point o = {0,0};
                    cout<<"Called Trans without O";
                    objeto->transform(string(elem->Attribute("transform")),o);
                }
            }
            //Apply group transformations
            for (pair<string, Point> trans : transformations){
                objeto->transform(trans.first,trans.second);
            }
            // Push_Back the final object with all transformations applied
            svg_elements.push_back(objeto);
        }  
        
        
        
        else if (string(elem->Name())=="polygon")
        {
            //Define a Polygon
            string points = elem->Attribute("points");
            vector <Point> poly = {};
            Point ponto;
            for(char &c: points){
                if (c==',' ){c=' ';}
            }
            istringstream turf(points);
            while(turf){
                turf>>ponto.x;
                turf>>ponto.y;
                poly.push_back(ponto);
            }
            Polygon* objeto = new Polygon(parse_color(elem->Attribute("fill")), poly);
            

            //Check if any transformation is applied, and transform if needed
            if (elem->Attribute("transform")!=0)
            {
                if (elem->Attribute("transform-origin")!=0)
                {
                    Point o;
                    string ori = elem->Attribute("transform-origin");
                    for(char &c: ori){
                        if (c==',' ){c=' ';}
                        if (c=='(' ){c=' ';}
                        if (c==')' ){c=' ';}
                    }
                    istringstream cogumelo(ori);
                    cogumelo>>o.x;
                    cogumelo>>o.y;
                    objeto->transform(string(elem->Attribute("transform")), o );
                } else{
                    Point o = {0,0};
                    cout<<"Called Trans without O";
                    objeto->transform(string(elem->Attribute("transform")),o);
                }
            }

            //Apply group transformations
            for (pair<string, Point> trans : transformations){
                objeto->transform(trans.first,trans.second);
            }

            // Push_Back the final object with all transformations applied
            svg_elements.push_back(objeto);
        } 
        

        // HANDLE GROUPS
        else if (string(elem->Name())=="g")
        {
            if (elem->Attribute("transform")!=0)
            {
                if (elem->Attribute("transform-origin")!=0)
                {
                    Point o;
                    string ori = elem->Attribute("transform-origin");
                    for(char &c: ori){
                        if (c==',' ){c=' ';}
                        if (c=='(' ){c=' ';}
                        if (c==')' ){c=' ';}
                    }
                    istringstream cogumelo(ori);
                    cogumelo>>o.x;
                    cogumelo>>o.y;
                    transformations.push_back(pair<string,Point>(string(elem->Attribute("transform")),o));
                } else{
                    Point o = {0,0};
                    transformations.push_back(pair<string,Point>(elem->Attribute("transform"),o));
                }
                
                //Recursive function call for the group (to be done)

                transformations.erase(transformations.end() - 1);
            }
        }
        
        //HANDLE USE's
        else if (string(elem->Name())=="use")
        {
            string ref = elem->Attribute("href");
            string id = ref.substr(1);
            vector<pair<string,Point>> t_temp = transformations;  //Create a temporary transformations vector to pass the group transformations applied to the use
            
            //Check if <use> has any transformation, and store it in vector
            if (elem->Attribute("transform")!=0)
            {
                if (elem->Attribute("transform-origin")!=0)
                {
                    Point o;
                    string ori = elem->Attribute("transform-origin") + 'x';
                    string cache = "";
                    for (char c : ori){
                        if ((c == ' ')&&(cache!=""))
                        {
                            o.x = stoi(cache);
                            cache = "";
                        } else if (c=='x')
                        {
                            o.y = stoi(cache);
                            cache = "";
                        } else if ((c>='0')&&(c<='9'))
                        {
                            cache += c;
                        }
                    }

                    t_temp.push_back(pair<string,Point>(elem->Attribute("transform"),o));
                } else{
                    Point o = {0,0};
                    t_temp.push_back(pair<string,Point>(elem->Attribute("transform"),o));
                }
            }

            use(root,root,id,svg_elements,t_temp);
            
        }
        

    
 
    for (XMLElement *child = elem->FirstChildElement(); child != nullptr; child = child->NextSiblingElement())
    {
        //std::cout<<"Dump "<<child->Name()<<"\n";
        readElements(root, child, svg_elements, transformations);
        //std::cout<<"Ended Dump "<<child->Name()<<"\n";
    }


    }



    void use(XMLElement *root, XMLElement *elem, string id ,vector<SVGElement *>& svg_elements, vector<pair<string,Point>> &transformations){

    // while (elem->)
    // {
    //     /* code */
    // }
    

    }







}