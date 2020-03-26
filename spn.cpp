#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <windows.h>
using namespace std;
using namespace sf;
typedef tuple<int,int,int> tiii;
priority_queue <tiii,vector<tiii>,greater<tiii> >pq1;
vector<vector<int> > tabla1;
#define PI tabla[pa][2]
#define TS tabla[pa][1]
#define H tabla[pa][0]
int h2,ts2,np2,PF2=0,pi2;
tiii ejecutando2=make_tuple(-1,-1,-1);
int promedio2=0;
void mostrar2(){
    cout<<setw(12)<<"NProceso"<<"\t";
    cout<<setw(12)<<"H.Llegada"<<"\t";
    cout<<setw(12)<<"T.Servicio"<<"\t";
    cout<<setw(12)<<"T.Final"<<"\t";
    cout<<setw(12)<<"T.Regreso"<<"\t"<<endl;
    for(int i=0;i<np2;i++){

        cout<<setw(12)<<i<<"\t";
        cout<<setw(12)<<tabla1[i][0]<<"\t";
        cout<<setw(12)<<tabla1[i][1]<<"\t";
        cout<<setw(12)<<tabla1[i][2]<<"\t";
        cout<<setw(12)<<tabla1[i][2]-tabla1[i][1]<<"\t";
        cout<<endl;
        promedio2+=(tabla1[i][2]-tabla1[i][1]);
    }
    cout<<"Tiempo promedio: "<<promedio2/np2<<endl;
}
typedef pair<int,int> pii;
priority_queue <pii,vector<pii>,greater<pii> >pq;
vector<vector<int> > tabla;
int h,ts,np,PF=0;
pii ejecutando=make_pair(-1,-1);
int promedio=0;
void mostrar(){
    cout<<setw(12)<<"NProceso"<<"\t";
    cout<<setw(12)<<"H.Llegada"<<"\t";
    cout<<setw(12)<<"T.Servicio"<<"\t";
    cout<<setw(12)<<"T.Final"<<"\t";
    cout<<setw(12)<<"T.Regreso"<<"\t"<<endl;
    for(int i=0;i<np;i++){

        cout<<setw(12)<<i<<"\t";
        cout<<setw(12)<<tabla[i][0]<<"\t";
        cout<<setw(12)<<tabla[i][1]<<"\t";
        cout<<setw(12)<<tabla[i][2]<<"\t";
        cout<<setw(12)<<tabla[i][2]-tabla[i][1]<<"\t";
        cout<<endl;
        promedio+=(tabla[i][2]-tabla[i][1]);
    }
    cout<<"Tiempo promedio: "<<promedio/np<<endl;
}
//si el contador es menor a la hora de llegada entonces el proceso de la h llegada se ejecuta y no va a la pila
vector<float>tiempo_final;
vector<float>tiempo_retorno;
vector<pair<int,pair<int,int>>> val;
void show()
{
	cout<<"Tiempo Final"<<"\t"<<"Tiempo de Retorno"<<endl;
	float promedio = 0;
	for (int i = 0; i < tiempo_final.size(); ++i)
	{
		cout<<tiempo_final[i]<<"\t"<<"\t"<<tiempo_retorno[i]<<endl;
		promedio += tiempo_retorno[i];
	}

	cout<<"Promedio: "<<promedio/tiempo_final.size()<<endl;
	tiempo_retorno.clear();
	tiempo_final.clear();
}


void roundrobin(int q)
{
	queue <pair<int,pair<int,int>>> servicio;
	tiempo_final.resize(val.size());
	tiempo_retorno.resize(val.size());
	sort(val.begin(),val.end());
	int posicion = 0;
	int t = 0;
	while(posicion < val.size())
	{
		int aumentar = posicion;
		for (int i = aumentar; i < val.size(); ++i)
		{
			if(val[i].first > t)
			{
				if(posicion) break;
				else t++;
			}

			if(val[i].first == t)
			{
			 	servicio.push(val[i]);
			 	posicion++;
			}
		}
		int tiempo_anterior;
		while(!servicio.empty())
		{
			tiempo_anterior = t;
			pair<int,pair<int,int>> aux = servicio.front();
			servicio.pop();
			cout << "Proceso ejecutandose "<<aux.second.second<<endl;
			if(aux.second.first >= q)
			{
				aux.second.first -= q;
				t += q;
			}
			else
			{
				t += aux.second.first;
				aux.second.first = 0;
			}
			aumentar = posicion;
			for (int i = aumentar; i < val.size(); ++i)
			{
				if(val[i].first <= t)
				{

				 	servicio.push(val[i]);
				 	posicion++;

				}
				else break;
			}

			if(aux.second.first != 0)
			{
				servicio.push(aux);
			}
			else
			{
				tiempo_final[aux.second.second-1] = t;
				tiempo_retorno[aux.second.second-1] = t - aux.first;
				cout << "El proceso "<<aux.second.second<<" ha finalizado"<<endl;
			}



		}
	}

	show();

}
int main()
{
   //
        cout<<"AlGORITMOS DE PLANIFICACIÓN"<<endl;
        cout<<"INGRESE 1 SI DESEA EJECUTAR FIFO"<<endl;
        cout<<"INGRESE 2 SI DESEA EJECUTAR SPN"<<endl;
        cout<<"INGRESE 3 SI DESEA EJECUTAR ROUND-ROBIN"<<endl;
        cout<<"INGRESE 4 SI DESEA EJECUTAR SRT"<<endl;
        cout<<"INGRESE 5 SI DESEA EJECUTAR PRIORIDADES NO APROPIATIVA"<<endl;
        cout<<"INGRESE 6 SI DESEA EJECUTAR PRIORIDADES APROPIATIVA"<<endl;
        int op;
        cin>>op;
    if(op==1)
    {
        vector<int>hl;
        vector<int>ts;
        int p;
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
            cout<<"Hora de llegada y Tiempo de Servicio"<<endl;
            cin>>hl[i]>>ts[i];
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
         int tf=0;
         float pf,prom;
         prom=0;
         cout<<"P"<<"\t"<<"H.L"<<"\t"<<"T.S"<<"\t"<<"T.F"<<"\t"<<"T.R"<<endl;
        for(int i=0;i<p ;i++)
        {
            tf=tf+ts[i];
            cout<<i<<"\t"<<hl[i]<<"\t"<<ts[i]<<"\t"<<tf<<"\t"<<tf-hl[i]<<endl;
            prom=tf;
        }
        cout<<"Tiempo Promedio "<<prom/p<<endl;
    }
    if(op==2)
    {
           vector<tuple<int,int,int>>vt;
           priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,greater<tuple<int,int,int>>>pq;
           cout<<"Numero de procesos"<<endl;
           int np,hl,p,ts;
           cin>>np;
           vt.resize(np);
           vector<tuple<int,int,int>>vt2;
           //
                vector<RectangleShape>celdas(np);
                vector<Text>contenido(np+1);
                vector<RectangleShape>celdas2(np);
                vector<Text>contenido2(np+1);
                sf::Vector2f dimensiones(150,60);
                Font fuente;
                if (!fuente.loadFromFile("arial.ttf"))
                {
                    return EXIT_FAILURE;
                }
           //
           for(int i=0;i<np;i++)
           {
               cout<<"Tiempo de Servicio, Proceso, Hora de llegada"<<endl;
               cin>>ts>>p>>hl;
               vt[i]=make_tuple(ts,p,hl);
           }
           int aux=0;
           //

                sf::RenderWindow ventana(sf::VideoMode(1080u,720u),"Simulacion");
                int c=200;
                int c2=200;
                //
                    Text cola;
                    cola.setFont(fuente);
                    cola.setString("Cola de ejecucion");
                    cola.setCharacterSize(20);
                    cola.setColor(Color::Red);
                    cola.setPosition(300,150);
                //
                    Text cola2;
                    cola2.setFont(fuente);
                    cola2.setString("Cola de Espera");
                    cola2.setCharacterSize(20);
                    cola2.setColor(Color::Yellow);
                    cola2.setPosition(480,150);
                //
           //
           for(int i=0;i<np;i++)
           {
               //
                celdas[i].setSize(dimensiones);
                celdas[i].setFillColor(sf::Color::Green);
                string j="";
                j=static_cast<std::ostringstream*>(&(std::ostringstream() << get<1>(vt[i])))->str();
                contenido[i].setFont(fuente);
                contenido[i].setString(j);
                contenido[i].setCharacterSize(20);
                contenido[i].setColor(Color::Blue);
                celdas[i].setPosition(300,c);
                contenido[i].setPosition(310,c+11);
                celdas2[i].setSize(dimensiones);
                celdas2[i].setFillColor(sf::Color::Red);
                string j2="";
                j2=static_cast<std::ostringstream*>(&(std::ostringstream() << get<1>(vt[i])))->str();
                contenido2[i].setFont(fuente);
                contenido2[i].setString(j2);
                contenido2[i].setCharacterSize(20);
                contenido2[i].setColor(Color::Blue);
                celdas2[i].setPosition(470,c2);
                contenido2[i].setPosition(480,c2+11);


            //

               if(aux>get<2>(vt[i])||get<2>(vt[i])==get<2>(vt[i+1]))
               {
                   pq.push(vt[i]);
                   ventana.draw(cola);
                   ventana.draw(cola2);
                   ventana.draw(celdas2[i]);
                   ventana.draw(contenido2[i]);
                   ventana.display();
                   ventana.clear();
                   Sleep(3000);
               }
               else if(aux<=get<2>(vt[i]))
               {
                 if(!pq.empty())
                 {
                   while(!pq.empty())
                   {
                       string k="";
                       k=static_cast<std::ostringstream*>(&(std::ostringstream() << get<1>(pq.top())))->str();
                       contenido[i].setString(k);
                       vt2.push_back(make_tuple(get<0>(pq.top()),get<1>(pq.top()),get<2>(pq.top())));
                       ventana.draw(cola);
                       ventana.draw(cola2);
                       ventana.draw(celdas[i]);
                       ventana.draw(contenido[i]);
                       ventana.display();
                       ventana.clear();
                       pq.pop();
                       Sleep(3000);
                   }
                 }

                       vt2.push_back(make_tuple(get<0>(vt[i]),get<1>(vt[i]),get<2>(vt[i])));
                       aux=aux+get<0>(vt[i]);
                       ventana.draw(cola);
                       ventana.draw(cola2);
                       ventana.draw(celdas[i]);
                       ventana.draw(contenido[i]);
                       ventana.display();
                       ventana.clear();
                       Sleep(3000);

               }

           }
           int i=0;
           if(!pq.empty())
           {

                while(!pq.empty())
                {
                       string k="";
                       k=static_cast<std::ostringstream*>(&(std::ostringstream() << get<1>(pq.top())))->str();
                       contenido[i].setFont(fuente);
                       contenido[i].setString(k);
                       vt2.push_back(make_tuple(get<0>(pq.top()),get<1>(pq.top()),get<2>(pq.top())));
                       pq.pop();
                       ventana.draw(cola);
                       ventana.draw(cola2);
                       ventana.draw(celdas[i]);
                       ventana.draw(contenido[i]);
                       ventana.display();
                       ventana.clear();
                       Sleep(3000);
                       i++;
                }
           }
           int tf;
           float prom,pf;
           prom=0;
           cout<<"P"<<"\t"<<"H.L"<<"\t"<<"T.S"<<"\t"<<"T.F"<<"\t"<<"T.R"<<endl;
           for(int i=0;i<np;i++)
           {

               if(i==0)
               {
                   tf=get<0>(vt2[i])+get<2>(vt2[i]);
               }
               else if(get<0>(vt2[i])>tf && i>0 && get<2>(vt[i])!=get<2>(vt[i+1]))
               {
                   tf=get<0>(vt2[i])+get<2>(vt2[i]);
               }
               else if((get<0>(vt2[i])<=tf && i>0)||(get<2>(vt[i])==get<2>(vt[i+1])))
               {
                   tf=tf+get<0>(vt2[i]);
               }
               cout<<get<1>(vt2[i])<<"\t"<<get<2>(vt2[i])<<"\t"<<get<0>(vt2[i])<<"\t"<<tf<<"\t"<<tf-get<2>(vt2[i])<<endl;
               prom=prom+tf-get<2>(vt2[i]);
               pf=prom;

           }
           cout<<"Tiempo Promedio "<<pf/np<<endl;

    }
    if(op==3)
    {
        int p,quantum;
        cout<<"Numero de procesos"<<endl;
        cin>>p;
        int hl,ts;
        for (int i = 0; i < p; ++i)
        {
            cout<<"Hora de llegada "<<"Tiempo de servicio"<<endl;
            cin>>hl>>ts;
            val.push_back(make_pair(hl,make_pair(ts,i+1)));
        }
        cout<<"Quantum"<<endl;
        cin>>quantum;
        roundrobin(quantum);
    }
    if(op==4)
    {
        cout<<"Ingrese numero procesos";cin>>np;
        tabla.assign(np+1,{});
        for(int i=0;i<=np;i++)tabla[i].assign(4,-1);
        for(int i=0;i<np;i++){
            cout<<"Hora de llegada y tiempo de servicio"<<endl;
            cin>>h>>ts;
            tabla[i][0]=h;
            tabla[i][1]=ts;
        }
        ejecutando=make_pair(tabla[0][1],0);
        int time=1,pa=1;
        do{
            cout<<"tiempo: "<<time;
            if(ejecutando.first!=-1)
                ejecutando=make_pair(ejecutando.first-1,ejecutando.second);
            if(ejecutando.first==0){
                    tabla[ejecutando.second][2]=time;
                    printf("\nProceso %d terminado\n",ejecutando.second);
                    if(!pq.empty()){
                        ejecutando=pq.top();
                        pq.pop();
                    }
                    else{
                        ejecutando=make_pair(-1,-1);
                    }
                    PF++;
                }
            if(time==tabla[pa][0]){
                if(ejecutando.first==-1){
                    ejecutando=make_pair(tabla[pa][1],pa);
                }
                else if(tabla[pa][1]<ejecutando.first){
                    cout<<" => cambio de proceso"<<endl;
                    pq.push(make_pair(ejecutando.first,ejecutando.second));
                    ejecutando=make_pair(tabla[pa][1],pa);
                }
                else{
                    pq.push(make_pair(tabla[pa][1],pa));
                }
                pa++;
            }
            else if(ejecutando.first==-1&&!pq.empty()){
                    ejecutando=pq.top();
                    pq.pop();
            }
            if(ejecutando.first==-1)cout<<"=> ningun proceso"<<endl;
            else
                cout<<"=> ejecutando: "<<ejecutando.second<<",con TS de: "<<ejecutando.first<<endl;
            time++;
        }while(np!=PF);

        mostrar();
    }
    if(op==5)
    {
                vector<tuple<int,float,float,float>>vt;
                   priority_queue<tuple<int,float,float,float>,vector<tuple<int,float,float,float>>,greater<tuple<int,float,float,float>>>pq;
                   cout<<"Numero de procesos"<<endl;
                   float hl,ts,pr;
                   int np,p;
                   cin>>np;
                   vt.resize(np);
                    vector<tuple<int,float,float,float>>vt2;
                    //
                    vector<RectangleShape>celdas(np);
                    vector<Text>contenido(np+1);
                    vector<RectangleShape>celdas2(np);
                    vector<Text>contenido2(np+1);
                    sf::Vector2f dimensiones(150,60);
                    Font fuente;
                    if (!fuente.loadFromFile("arial.ttf"))
                    {
                            return EXIT_FAILURE;
                    }


                   for(int i=0;i<np;i++)
                   {
                       cout<<"Proceso, Hora de llegada, Tiempo de Servicio, Prioridad"<<endl;
                       cin>>p>>hl>>ts>>pr;
                       vt[i]=make_tuple(pr,hl,ts,p);
                   }
                    sf::RenderWindow ventana(sf::VideoMode(1080u,720u),"Simulacion");
                    int c1=200;
                    int c2=200;
                    //
                        Text cola;
                        cola.setFont(fuente);
                        cola.setString("Cola de ejecucion");
                        cola.setCharacterSize(20);
                        cola.setColor(Color::Red);
                        cola.setPosition(300,150);
                                //
                        Text cola2;
                        cola2.setFont(fuente);
                        cola2.setString("Cola de Espera");
                        cola2.setCharacterSize(20);
                        cola2.setColor(Color::Yellow);
                        cola2.setPosition(480,150);

                    float c=0.0;
                    for(int i=0;i<np;i++)
                   {
                        celdas[i].setSize(dimensiones);
                        celdas[i].setFillColor(sf::Color::Green);
                        string j="";
                        j=static_cast<std::ostringstream*>(&(std::ostringstream() << get<3>(vt[i])))->str();
                        contenido[i].setFont(fuente);
                        contenido[i].setString(j);
                        contenido[i].setCharacterSize(20);
                        contenido[i].setColor(Color::Blue);
                        celdas[i].setPosition(300,c1);
                        contenido[i].setPosition(310,c1+11);
                        celdas2[i].setSize(dimensiones);
                        celdas2[i].setFillColor(sf::Color::Red);
                        string j2="";
                        j2=static_cast<std::ostringstream*>(&(std::ostringstream() << get<3>(vt[i])))->str();
                        contenido2[i].setFont(fuente);
                        contenido2[i].setString(j2);
                        contenido2[i].setCharacterSize(20);
                        contenido2[i].setColor(Color::Blue);
                        celdas2[i].setPosition(470,c2);
                        contenido2[i].setPosition(480,c2+11);
                       if(i==0)
                       {

                          vt2.push_back(make_tuple(get<0>(vt[i]),get<1>(vt[i]),get<2>(vt[i]),get<3>(vt[i])));
                          ventana.draw(cola);
                          ventana.draw(cola2);
                          ventana.draw(celdas[i]);
                          ventana.draw(contenido[i]);
                          ventana.display();
                          ventana.clear();
                          Sleep(3000);
                          c=c+get<2>(vt[i]);

                       }
                      else
                      {
                        cout<<c<<endl;
                        if(c>get<1>(vt[i]))
                        {
                           pq.push(vt[i]);
                           ventana.draw(cola);
                           ventana.draw(cola2);
                           ventana.draw(celdas2[i]);
                           ventana.draw(contenido2[i]);
                           ventana.display();
                           ventana.clear();
                           Sleep(3000);
                        }
                        else if(c<=get<1>(vt[i]))
                        {
                          if(!pq.empty())
                           {
                               while(!pq.empty())
                             {
                                string k="";
                                k=static_cast<std::ostringstream*>(&(std::ostringstream() << get<3>(pq.top())))->str();
                                contenido[i].setString(k);
                                vt2.push_back(make_tuple(get<0>(vt[i]),get<1>(vt[i]),get<2>(vt[i]),get<3>(vt[i])));
                                ventana.draw(cola);
                                ventana.draw(cola2);
                                ventana.draw(celdas[i]);
                                ventana.draw(contenido[i]);
                                ventana.display();
                                ventana.clear();
                                pq.pop();
                                Sleep(3000);
                             }
                           }
                               vt2.push_back(make_tuple(get<0>(vt[i]),get<1>(vt[i]),get<2>(vt[i]),get<3>(vt[i])));
                               ventana.draw(cola);
                               ventana.draw(cola2);
                               ventana.draw(celdas[i]);
                               ventana.draw(contenido[i]);
                               ventana.display();
                               ventana.clear();
                               Sleep(3000);

                        }
                        c=c+get<2>(vt[i]);
                      }

                    }
                        int i=0;
                    if(!pq.empty())
                    {
                        while(!pq.empty())
                        {
                                string k="";
                                k=static_cast<std::ostringstream*>(&(std::ostringstream() << get<3>(pq.top())))->str();
                                contenido[i].setFont(fuente);
                                contenido[i].setString(k);
                               vt2.push_back(make_tuple(get<0>(vt[i]),get<1>(vt[i]),get<2>(vt[i]),get<3>(vt[i])));
                                pq.pop();
                                ventana.draw(cola);
                                ventana.draw(cola2);
                                ventana.draw(celdas[i]);
                                ventana.draw(contenido[i]);
                                ventana.display();
                                ventana.clear();
                                Sleep(3000);
                                i++;
                        }
                    }
                    float tf=0;
                   float prom,pf;
                   prom=0;
                   cout<<"P"<<"\t"<<"H.L"<<"\t"<<"T.S"<<"\t"<<"Pr"<<"\t"<<"T.F"<<"\t"<<"T.R"<<endl;
                   for(int i=0;i<np;i++)
                   {
                       if(i==0)
                       {
                           tf=tf+get<1>(vt2[i])+get<2>(vt2[i]);
                       }
                       else if(tf<=get<1>(vt2[i]))
                       {
                           tf=get<2>(vt2[i])+get<1>(vt2[i]);
                       }
                       else if(tf>get<1>(vt2[i]))
                       {
                           tf=tf+get<2>(vt2[i]);
                       }
                       cout<<get<3>(vt2[i])<<"\t"<<get<1>(vt2[i])<<"\t"<<get<2>(vt2[i])<<"\t"<<get<0>(vt2[i])<<"\t"<<tf<<"\t"<<tf-get<1>(vt2[i])<<endl;
                       prom=prom+tf-get<1>(vt2[i]);
                       pf=prom;
                   }
                   cout<<"Tiempo Promedio "<<pf/np<<endl;

    }
    if(op==6)
    {
            cout<<"Ingrese numero procesos";cin>>np;
            tabla1.assign(np2+1,{});
            for(int i=0;i<=np2;i++)tabla1[i].assign(4,-1);
            for(int i=0;i<np2;i++){
                cout<<"Hora de llegada, tiempo de servicio y prioridad"<<endl;
                cin>>h2>>ts2>>pi2;
                tabla1[i][0]=h2;
                tabla1[i][1]=ts2;
                tabla1[i][3]=pi2;
            }
            ejecutando2=make_tuple(tabla1[0][3],tabla1[0][1],0);
            int time=1,pa=1;
            do{
                cout<<"tiempo: "<<time;
                if(get<0>(ejecutando2)!=-1)
                    ejecutando2=make_tuple(get<0>(ejecutando2),get<1>(ejecutando2)-1,get<2>(ejecutando2));
                if(get<1>(ejecutando2)==0){
                        tabla1[get<2>(ejecutando2)][2]=time;
                        printf("\nProceso %d terminado\n",get<2>(ejecutando2));
                        if(!pq1.empty()){
                            ejecutando2=pq1.top();
                            pq1.pop();
                        }
                        else{
                            ejecutando2=make_tuple(-1,-1,-1);
                        }
                        PF2++;
                    }
                if(time==tabla1[pa][0]){
                    if(get<0>(ejecutando2)==-1){
                        ejecutando2=make_tuple(tabla1[pa][3],tabla1[pa][1],pa);
                    }
                    else if(tabla1[pa][3]<get<0>(ejecutando2)){

                        cout<<" => cambio de proceso"<<endl;
                        pq1.push(make_tuple(get<0>(ejecutando2),get<1>(ejecutando2),get<2>(ejecutando2)));
                        ejecutando2=make_tuple(tabla1[pa][3],tabla1[pa][1],pa);
                    }
                    else{
                        pq1.push(make_tuple(tabla1[pa][3],tabla1[pa][1],pa));
                    }
                    pa++;
                }

                if(get<0>(ejecutando2)==-1)cout<<"=> ningun proceso"<<endl;
                else
                    cout<<"=> ejecutando: "<<get<2>(ejecutando2)<<",con TS de: "<<get<1>(ejecutando2)<<endl;
                time++;
            }while(np2!=PF2);

            mostrar2();
    }

}
