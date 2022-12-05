#include <Windows.h>
#include <conio.h>
#include "SceneManager.h"

using namespace std;

int main()
{

       
    cout << "Nome:Filipe Martin Santos                                             Unisinos 2022/2   " << endl;

    cout << "\n--------------------------------The Game Awards 2022--------------------------------\n" << endl;
       
    cout << "1 - Elden Ring" << endl;
    cout << "2 - God of War: Ragnarok" << endl;
    cout << "3 - Horizon: Forbidden West" << endl;
    cout << "4 - A Plague Tale: Requiem" << endl;
    cout << "5 - Stray" << endl;
    cout << "6 - Xenoblade Chronicles 3" << endl;

    cout << "\n\n\n\nUse as teclas abaixo para aplicar o filtro: \n"
        "1: habilitar somente o canal vermelho\n"
        "2: habilitar somente o canal verde\n"
        "3: habilitar somente o canal azul\n"
        "4: filtro de grayScale\n"
        "5: filtro de somar cor\n"
        "6: filtro de inversao\n"
        "7: filtro de binarizacao\n"
        "8: transforma pixels bem escuros em brancos\n"
        "Z: Amarelo\n"
        "X: Roxo\n"
        "C: Azul Claro\n"
        "V: Laranja\n"
        << endl;
    
    char choice;
    string path;
    
    while (true)
    {
        choice = _getch();
        if (choice == '1')
        {
            path = "../textures/Elden ring.jpg";
            break;
        }
        else if (choice == '2')
        {
            path = "../textures/god_of_war.jpg";
            break;
        }
        else if (choice == '3')
        {
            path = "../textures/Horizon.jpg";
            break;
        }
        else if (choice == '4')
        {
            path = "../textures/Plague Tale.jpg";
            break;
        }
        else if (choice == '5')
        {
            path = "../textures/stray.jpg";
            break;
        }
        else if (choice == '6')
        {
            path = "../textures/xenoblade 3.jpg";
            break;
        }
    }

    SceneManager* sceneManager = new SceneManager();
    sceneManager->initialize(1800, 1000, "TrabalhoGB Filipe Martin", path);

    sceneManager->run(Ponto3d(1,1,1));
}