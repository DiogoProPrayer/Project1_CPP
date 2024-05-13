 else if (elemname=="polyline") {
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
            Polyline* x = new Polyline(parse_color(elem->Attribute("stroke")), cluster);
            svg_elements.push_back(x);
}



else if (elemname=="polygon")
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
            Polygon* x = new Polygon(parse_color(elem->Attribute("fill")), poly);
            svg_elements.push_back(x);
}
