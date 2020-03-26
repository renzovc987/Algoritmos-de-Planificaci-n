#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <windows.h>
using namespace std;
using namespace sf;

int main()
{
    vector<int>hl;
    vector<int>ts;
    int p,tf;
    tf=0;
    cout<<"Numero de procesos"<<endl;
    cin>>p;
    hl.resize(p);
    ts.resize(p);
    vector<RectangleShape>celdas(p);
    vector<Text>contenido(p+1);
    sf::Vector2f dimensiones(150,60);
    Font fuente;
    if (!fuente.loadFromFile("arial.ttf"))
	{
		return EXIT_FAILURE;
	}
    for(int i=0;i<p;i++)
    {
        cin>>ts[i]>>hl[i];
    }
    //cout<<"P"<<"\t"<<"H.L"<<"\t"<<"T.S"<<"\t"<<"T.F"<<"\t"<<"T.R"<<endl;
    sf::RenderWindow ventana(sf::VideoMode(1080u,720u),"Simulacion");

    int c=200;
    Text cola;
    cola.setFont(fuente);
    cola.setString("Cola de ejecucion");
    cola.setCharacterSize(20);
    cola.setColor(Color::Red);
    cola.setPosition(300,150);



    int colu;

    int i=0;
    while(p>i)
    {
        /*tf=tf+ts[j];
        cout<<j+1<<"\t"<<hl[j]<<"\t"<<ts[j]<<"\t"<<tf<<"\t"<<tf-hl[j]<<endl;*/
        celdas[i].setSize(dimensiones);
        celdas[i].setFillColor(sf::Color::Green);
        string j="";
        j=static_cast<std::ostringstream*>(&(std::ostringstream() << i+1 << " HL: "<<hl[i]<<" TS: "<<ts[i]))->str();
        contenido[i].setFont(fuente);
        contenido[i].setString(j);
        contenido[i].setCharacterSize(20);
        contenido[i].setColor(Color::Blue);
        celdas[i].setPosition(300,c);
        contenido[i].setPosition(310,c+11);
        c=c+75;
        colu=c;
        ventana.draw(cola);
        ventana.draw(celdas[i]);
        ventana.draw(contenido[i]);
        ventana.display();
        ventana.clear();
        Sleep(3000);
        i++;
    }
    Sleep(3000);


}

