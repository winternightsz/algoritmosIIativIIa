#include <iostream>
#include <string>
#include <Windows.h>
#include <locale.h>
#include <time.h>
#include <ctime>

using namespace std;

/*STRUCTS*/
struct Autor {

    string Nome;

};
struct Editora {

    string Nome;

};
struct Livro {

    string Titulo;
    string Assunto;
    int Id=0;
    Autor Autor;
    Editora Editora;
    int IDuser;
    bool Retirado=false; //pra registrar o livro
  
};
struct Revista {

    string Titulo;
    string Assunto;
    Editora Editora;

};
struct Usuario {

    int Id=0;
    string Nome;
    

};
struct tm Datadevolucao; //para poder usar as funcoes de tm_day e afins para dizer dia de devolucao e contar os atrasos

/*MAX COISAS*/
const int maxlivros = 20;
const int maxrevistas = 20;
const int maxusers = 20;
const int maxeditora = 20;
const int maxautor = 20;

/*ARRAYS*/
Livro livros[maxlivros];
Revista revista[maxrevistas];
Autor autor[maxautor];
Editora editora[maxeditora];
Usuario users[maxusers];

/*CADASTRAR E ALTERAR AUTOR*/
void cadastroautor(Autor autor[], int &contautores) { //o & pra poder fazer apartir do 4 e ir mudando no array
    Autor autores;
    
    while (true) {
        if (contautores >= maxautor) {
            cout << "Foi atigindo o numero maximo de autores." << endl;
            break;
        }

        cout << "Digite o nome do autor "<< contautores <<":" << endl;
        cin >> autor[contautores].Nome;

        contautores++;

        cout << "Deseja cadastrar mais um autor? S para sim e N para nao: ";
        char escolha;
        cin >> escolha;
        if (escolha == 'n' || escolha == 'N') {
            break;
        }
    }

    cout << "Autores cadastrados:" << endl;
    for (int i = 0; i < contautores; i++) {
        cout << i + 1 << ". " << autor[i].Nome << endl;
    }
}
void alterarautor(Autor autores[]) {
    int escolha;
    cout << "Selecione o autor que deseja alterar: " << endl;
    for (int i = 0; i < maxautor; i++) {
        cout << i << ". " << autores[i].Nome << endl;
    }
    cin >> escolha;

    
    if (escolha < 0 || escolha >= maxautor) {
        cout << "Opcao invalida" << endl;
        return;
    }

    // pede ao usuario para digitar o novo nome do autor
    cout << "Digite o novo nome do autor: ";
    cin >> autores[escolha].Nome;                   //vai ir no array do autor especifico e alterar o nome

    cout << "Autor alterado com sucesso!" << endl;
}

/*CADASTRAR E ALTERAR EDITORA*/
void cadastroeditora(Editora editor[], int &conteditor) {
    Editora editores;
    
    while (true) {
        if (conteditor >= maxeditora) {
            cout << "Foi atigindo o numero maximo de editoras." << endl;
            break;
        }

        cout << "Digite o nome da Editora " << conteditor << ":" << endl;
        cin >> editor[conteditor].Nome;

        conteditor++;

        cout << "Deseja cadastrar mais uma Editora? S para sim e N para nao: ";
        char escolha;
        cin >> escolha;
        if (escolha == 'n' || escolha == 'N') {
            break;
        }
    }

    cout << "Editoras cadastradas:" << endl;
    for (int i = 0; i < conteditor; i++) {
        cout << i + 1 << ". " << editor[i].Nome << endl;
    }
}
void alterareditora(Editora editor[]) {
    int escolha;
    cout << "Selecione o editora que deseja alterar: " << endl;
    for (int i = 0; i < maxeditora; i++) {
        cout << i << ". " << editor[i].Nome << endl;
    }
    cin >> escolha;

    
    if (escolha < 0 || escolha >= maxeditora) {
        cout << "Opcao invalida." << endl;
        return;
    }

    
    cout << "Digite o novo nome do autor: ";
    cin >> editor[escolha].Nome;

    cout << "Editora alterada com sucesso!" << endl;
}

/*CADASTRO USUARIO*/
void cadastrousuario(Usuario users[], int &i ) {
    int continuar = 1;
    do {
      

        int id;
        
        do {
            cout << "Usuario " << i << ":" << endl;
            cout << "Digite um codigo de 5 digitos (1 a 9): ";
            cin >> id;
        } while (id < 11111 || id > 99999); // verifica se o codigo tem 5 dígitos e vai ser entre 11111 e 99999

        
        bool existe = false;//vai verificar se o codigo ja existe
        for (int j = 0; j < i; j++) {

            if (users[j].Id == id) { 

                existe = true; //se existir ele entra na funcao do if
                break;
            }
        }
        if (existe) {
            cout << "Esse codigo ja foi cadastrado." << endl;
            continue;
        }

      

        cout << "Digite um nome: ";
        cin.ignore();
        getline(cin, users[i].Nome);
        users[i].Id = id; //vai colocar o codigo do usuario em relacao a ele mesmo
        i++;

        cout << "Deseja sair? precione 1 para nao e 0 para sim: ";
        cin >> continuar;
    } while (continuar != 0);
}


/*CADASTRAR LIVRO*/
void cadastrolivro(Livro livros[], Autor autores[], Editora editoras[], int &contlivro) {
    
    
    bool continuar = true;

    while (continuar) {
        cout << "Digite o titulo do livro " << contlivro << ":" << endl;
        cin.ignore();
        getline(cin, livros[contlivro].Titulo);

        cout << "Digite o assunto do livro: ";
        getline(cin, livros[contlivro].Assunto);

       
        cout << "Autores cadastrados: " << endl;
        for (int j = 0; j < maxautor; j++) {
            cout << j << ". " << autores[j].Nome << endl;
        }

        //vai pedir pro usuario digitar e vai verificar se pode 
        int escolha;
        do {
            cout << "Digite o número do autor: ";
            cin >> escolha;
        } while (escolha < -1 || escolha >= maxautor); 

        livros[contlivro].Autor = autores[escolha]; //vai igualar o autor no autor do struct dos livros pra salvar
        
              

        cout << "Editoras cadastradas: " <<endl;
        for (int j = 0; j < maxeditora; j++) {
            cout << j << ". " << editoras[j].Nome << endl;
        }


        //vai pedir pro usuario digitar e vai verificar se pode essa opcao
        do {
            cout << "Digite o número da editora: ";
            cin >> escolha;
        } while (escolha < -1 || escolha >= maxeditora); 

        livros[contlivro].Editora = editoras[escolha];


        
        srand(time(NULL));
        livros[contlivro].Id = rand() % 100000; // vai gerar um número aleatório entre 0 e 99999
        livros[contlivro].Id = livros[contlivro].Id + 10000; // adiciona 10000 para garantir que o código tenha 5 dígitos
        livros[contlivro].Id = livros[contlivro].Id % 100000; // remove o primeiro digito pra se o ficar maior que 99999
        if (livros[contlivro].Id < 10000) {
            livros[contlivro].Id = livros[contlivro].Id + 10000; //so vai adicionar se tiver menos que 5 digitos
        }
        cout << "O código gerado para este livro é: " << livros[contlivro].Id << endl;
        contlivro++;

        
        char resposta;//perguntar ao usuario quer continuar cadastrando livros
        do {
            cout << "Deseja cadastrar outro livro? S para sim e N para nao ";
            cin >> resposta;
        } while (resposta != 'S' && resposta != 's' && resposta != 'N' && resposta != 'n');

        if (resposta == 'N' || resposta == 'n') {
            continuar = false;
        }
    }

    cout << "Cadastro de livros finalizado." << endl;
}
void alterarlivro(Livro livros[], Autor autores[], Editora editoras[]) {
    int escolha;
    cout << "Selecione o livro que deseja alterar: " << endl;
    for (int i = 0; i < maxlivros; i++) {
        cout << i << ". " << livros[i].Titulo << endl;
    }
    cin >> escolha;

   
    if (escolha < 0 || escolha >= maxlivros) {
        cout << "opcao invalida." << endl;
        return;                             //verificacao
    }

    //botar as novas informacoes do livro
    cout << "Digite o novo titulo do livro: ";
    getline(cin, livros[escolha].Titulo);

    cout << "Digite o novo assunto do livro: ";
    getline(cin, livros[escolha].Assunto);

    //vai verificar se o autor existe e atualiza o valor no array de livros
    int opdoautor;
    cout << "Selecione o autor do livro: " << endl;
    for (int i = 0; i < maxautor; i++) {
        cout << i << ". " << autores[i].Nome << endl;
    }
    cin >> opdoautor;

    if (opdoautor < 0 || opdoautor >= maxautor) {
        cout << "Autor invalido." << endl;
        return;
    }

    livros[escolha].Autor = autores[opdoautor];


    int opdoeditor;
    cout << "Selecione a editora do livro: " << endl;
    for (int i = 0; i < maxeditora; i++) {
        cout << i << ". " << editoras[i].Nome << endl;
    }
    cin >> opdoeditor;

    if (opdoeditor < 0 || opdoeditor >= maxeditora) {
        cout << "Editora invalida." << endl;
        return;
    }

    livros[escolha].Editora = editoras[opdoeditor];

    cout << "Livro alterado com sucesso!" << endl;
}


/*CADASTRAR REVISTA*/
void cadastrorevista(Revista rev[], Editora edit[], int &i) {
   

    do {
        cout << "Digite o titulo da Revista " << i << ":" << endl;
        getline(cin, rev[i].Titulo);

        cout << "Digite o assunto da Revista: ";
        getline(cin, rev[i].Assunto);

        cout << "Editoras cadastradas: " << endl;
        for (int j = 0; j < maxeditora; j++) {
            cout << j << ". " << edit[j].Nome << endl;
        }

      
        int escolha;
        do {
            cout << "Digite o número da editora: ";
            cin >> escolha;
        } while (escolha < -1 || escolha >= maxeditora); 

        rev[i].Editora = edit[escolha];
        i++;

       
        cout << "Deseja cadastrar mais uma revista? S para sim e N para nao: ";
        char escolhas;
        cin >> escolhas;
        cin.ignore(); 

        if (escolhas == 'n' || escolhas == 'N' || i >= maxrevistas) {
            break;
        }
    } while (true);

    cout << "Cadastrado com Sucesso!" << endl;
}


/*FUNCOES*/

void retirarLivro(Usuario users[], Livro livros[], Autor autor[], Editora edit[]) {
    Usuario user;
    Livro livro;
    bool livroEncontrado = false;
    bool userEncontrado = false;
    int idUser;
    int idLivro;

   //vai pedir o id do usuario pra que possa saber quem tirou o livro depois
    cout << "Digite seu ID: ";
    cin >> idUser;

    //verificacao de se existe o usuario
    for (int i = 0; i < maxusers; i++) {
        if (users[i].Id == idUser) {
            userEncontrado = true;
            break;
        }
    }

    if (!userEncontrado) {
        cout << "Usuario nao encontrado!" << endl;
        return;
    }

    cout << "Livros disponiveis para retirada:" << endl;
    for (int i = 0; i < maxlivros; i++) {
        if (livros[i].Retirado == false) {
            cout << livros[i].Id << ". " << livros[i].Titulo << " - " << endl;
        }
    }

    //pede o id do livro que quer tirar
    do {
        cout << "Digite o ID do livro que deseja retirar: ";
        cin >> idLivro;

        //verificacao de se existe e se ja foi retirado
        for (int i = 0; i < maxlivros; i++) {
            if (livros[i].Id == idLivro) {
                livroEncontrado = true;

                
                if (livros[i].Retirado == true) {
                    cout << "Este livro ja foi retirado" << endl;
                    livroEncontrado = false;
                    break;
                }

                //se passar pelos de cima vai registrar 
                livros[i].Retirado = true;
                livros[i].IDuser = idUser;
                cout << "Livro " << livros[i].Titulo << " retirado com sucesso!" << endl;
                break;
            }
        }

        if (!livroEncontrado) {
            cout << "Livro nao encontrado. Escolha de novo." << endl;
        }

    } while (!livroEncontrado);

    cout << "Livro escolhido: " << livro.Titulo << endl;

    // Calcula a data de devolucao 
    time_t agora = time(0); //pra ter a data e hora atuais
    
    localtime_s(&Datadevolucao, &agora); //usa a datadevolucao da struct de tm e o agora da de time_t
    Datadevolucao.tm_mday += 7; //adiciona 7 dias pro tm_day
    mktime(&Datadevolucao); //vai converter a estrutura do tm para uma de time_t
    cout << "Livro retirado com sucesso. Devolva ate " << Datadevolucao.tm_mday << "/" << Datadevolucao.tm_mon + 1 << "/" << Datadevolucao.tm_year + 1900 << endl;
    return;
    
}

void listagematrasos(Usuario users[], Livro livros[]) {
    Usuario user;
    int userID;
    bool livroEncontrado = false;
    bool userEncontrado = false;

    
    time_t agora = time(0);

    
    cout << "Digite seu ID: ";
    cin >> userID;

    //verificacao
    for (int i = 0; i < maxusers; i++) {
        if (users[i].Id == userID) {
            userEncontrado = true;
            break;
        }
    }

    if (!userEncontrado) {
        cout << "Usuario nao foi encontrado!" << endl;
        return;
    }

    //vai checar ser tem livro atrasado e se tiver vai mostrar
    bool temlivroatraso = false;
    for (int i = 0; i < maxlivros; i++) {
        Livro livro = livros[i]; //vai pegar o livro do array e passar pra variavel
        if (Datadevolucao.tm_mday != 0 && Datadevolucao.tm_mday < agora && livro.IDuser == userID) {
            temlivroatraso = true;                                                                   //se foi diferente de 0 menor q o dia de hj e os ids forem iguais dai entra
            if (temlivroatraso) {
                cout << "Esses livros estao em atraso: " << endl;
                
            }
            cout << livro.Titulo <<endl ;
        }
    }

   
    if (!temlivroatraso) {
        cout << "Nao existem nenhum livro em atraso para o usuario: " << userID << endl;
    }
}

void historicaretirados(Usuario users[], Livro livros[]) {
    int idUser;
    bool userEncontrado = false;

    
    do {
        cout << "Digite o ID do usuario para ver o historico de retiradas: ";
        cin >> idUser;
    } while (idUser < 11111 || idUser > 99999);

    
    for (int i = 0; i < maxusers; i++) {
        if (users[i].Id == idUser) {
            userEncontrado = true;
            break;
        }
    }

    if (!userEncontrado) {
        cout << "Usuario nao foi encontrado." << endl;
        return;
    }

    Livro livrosRetirados[maxlivros]; //cria um array pros livros retirados
    int numret = 0; //contador pros livros retirados

    // Filtrar livros retirados pelo usuario
    for (int i = 0; i < maxlivros; i++) {
        if (livros[i].Retirado && livros[i].IDuser == idUser) { //checa o id com o id de quem retirou
            livrosRetirados[numret] = livros[i]; //livros retirados adquiri o nome no array
            numret++;
        }
    }

    if (numret == 0) {
        cout << "Usuario nao contem nenhum livro retirado" << endl;
    }
    else {
        cout << "Historico de retiradas:" << endl;
        for (int i = 0; i < numret; i++) {
            cout << "Livro: " << livrosRetirados[i].Titulo << endl;
        }
    }
}

void listagemautores(Autor autor[])
{
    cout << "Lista de Autores" << endl;
    for (int i = 0; i < maxautor; i++) {
        cout << "Nome do Autor: " << autor[i].Nome << endl;

    }
};
void listagemeditora(Livro livros[], Revista rev[]) {
    cout << "Lista das Editoras" << endl;
    for (int i = 0; i < maxlivros; i++) {
        cout << "Nome das Editora Livro: " << livros[i].Editora.Nome << endl;
    }
    cout << endl;
    for (int i = 0; i < maxrevistas; i++) {
        cout << "Nome Editora Revista: " << rev[i].Editora.Nome << endl ;
    }
};
void listagemlivro(Livro livros[], Autor autor[], Editora edit[]) {
    cout << "Lista de Livros" << endl;
    for (int i = 0; i < maxlivros; i++) {
        cout << "ID: " << livros[i].Id << endl;
        cout << "Titulo: " << livros[i].Titulo << endl;
        cout << "Assunto: " << livros[i].Assunto << endl;
        cout << "Autor: " << livros[i].Autor.Nome << endl;
        cout << "Editora: " << livros[i].Editora.Nome << endl << endl;


    }
};
void listagemrevista(Revista rev[], Editora edit[]) {
    cout << "Lista das Revistas" << endl;
    for (int i = 0; i < maxrevistas; i++) {
        cout << "Titulo: " << rev[i].Titulo << endl;
        cout << "Assunto: " << rev[i].Assunto << endl << endl;
        cout << "Editora: " << rev[i].Editora.Nome << endl << endl;


    }
};
void listagemassuntos(Livro livros[], Revista rev[]) {
    cout << "Lista dos Assuntos" << endl;
    for (int i = 0; i < maxlivros; i++) {
        cout << "Assuntos livros: " << livros[i].Assunto << endl;
    }
    cout << endl;
    for (int i = 0; i < maxrevistas; i++) {
        cout << "Assuntos revistas: " << rev[i].Assunto << endl;
    }
};

void pesquisaritem(Livro livros[], Revista rev[], Autor autores[], Editora editoras[], int opcao) {

    string busca;

    switch (opcao) {
        case 1: {
            cout << "Digite o titulo que deseja pesquisar: ";
            cin.ignore();
            getline(cin, busca);

            for (int i = 0; i < maxlivros; i++) {
                if (livros[i].Titulo == busca) {             //se busca iguala ao item dentro do array entao ele mostra oque achou
                    cout << "Livro encontrado:" << endl;
                    cout << "Titulo: " << livros[i].Titulo << endl;
                    cout << "Autor: " << livros[i].Autor.Nome << endl;
                    cout << "Editora: " << livros[i].Editora.Nome << endl;
                    cout << "Assunto: " << livros[i].Assunto << endl;
                    return;
                }
                else if (rev[i].Titulo == busca) {
                    cout << "Revista encontrada:" << endl;
                    cout << "Titulo: " << rev[i].Titulo << endl;
                    cout << "Editora: " << rev[i].Editora.Nome << endl;
                    cout << "Assunto: " << rev[i].Assunto << endl;
                    return;
                }
            }

            cout << "Titulo nao encontrado." << endl;
            break;
        }
        case 2: {
            cout << "Digite o nome do autor que deseja pesquisar: ";
            cin.ignore();
            getline(cin, busca);

            for (int i = 0; i < maxautor; i++) {
                if (autores[i].Nome == busca) {
                    cout << "Autor encontrado:" << endl;
                    cout << "Nome: " << autores[i].Nome << endl;

                    return;
                }
            }

            cout << "Autor nao encontrado." << endl;
            break;
        }
        case 3: {
            cout << "Digite o nome da editora que deseja pesquisar: ";
            cin.ignore();
            getline(cin, busca);

            for (int i = 0; i < maxeditora; i++) {
                if (editoras[i].Nome == busca) {
                    cout << "Editora encontrada:" << endl;
                    cout << "Nome: " << editoras[i].Nome << endl;

                    return;
                }
            }

            cout << "Editora nao encontrada." << endl;
            break;
        }
        case 4: {
            cout << "Digite o nome do assunto que deseja pesquisar: ";
            cin.ignore();
            getline(cin, busca);

            for (int i = 0; i < maxlivros; i++) {
                if (livros[i].Assunto == busca) {
                    cout << "Assunto em livro encontrado:" << endl;
                    cout << "Título: " << livros[i].Titulo << endl;
                    cout << "Autor: " << livros[i].Autor.Nome << endl;
                    cout << "Editora: " << livros[i].Editora.Nome << endl;
                    cout << "Assunto: " << livros[i].Assunto << endl;
                }
                else if (rev[i].Assunto == busca) {
                    cout << "Assunto em revista encontrada:" << endl;
                    cout << "Titulo: " << rev[i].Titulo << endl;
                    cout << "Editora: " << rev[i].Editora.Nome << endl;
                    cout << "Assunto: " << rev[i].Assunto << endl;
                    return;
                }
            }
            cout << "Assunto nao encontrado." << endl;
        }
    }
}

int main()
{
    
    Livro livros[maxlivros] = {
    {"Harry Potter","Ficcao", 68467, "JK Rowling", "Editora Rocco", 65473, true},
    {"Morte no Nilo","Terror", 68468, "Agatha Christie", "Editora Rocco", 0, false },
    {"Great Gatsby","Romance", 68465, "Scott Fitzgerald", "Editora Arqueiro", 0, false } };
    livros[1].Assunto = { "Ficcao" };
    livros[2].Assunto = { "Romance" };
    livros[3].Assunto = { "Terror" };

    Revista revista[maxrevistas] = {
    {"Harry Potter", "Ficcao","Editora Rocco"},
    { "Morte no Nilo","Terror","Editora Rocco" },
    { "Great Gatsby","Romance","Editora Arqueiro"}
    };
    revista[1].Assunto = { "Ficcao" };
    revista[2].Assunto = { "Romance" };
    revista[3].Assunto = { "Terror" };
    Autor autor[maxautor] = { "Agatha Christie", "JK Rowling", "Scott Fitzgerald", "", "", "", "", "", "", "" };
    Editora editora[maxeditora] = { "Editora Rocco", "Companhia das Letras", "Editora Arqueiro", "", "", "", "", "", "", "" };
    Usuario users[maxusers] = {
        {87654,"John"},
        {76543,"Peter"}
    };
    int escolha;
    int usercont = 2;
    int livrocont = 4;
    int revistacont = 4;
    int autorcont = 4;
    int editoracont = 4;


    do {
        cout << endl << "Escolha uma opcao:" << endl;
        cout << "\t1 - Cadastro dos usuarios" << endl;
        cout << "\t2 - Cadastro para livros e Revistas e afins" << endl;
        cout << "\t3 - Alterar livros, autores e editoras" << endl;
        cout << "\t4 - Listagem de Livros e Revistas e afins" << endl;
        cout << "\t5 - Pesquisar" << endl;
        cout << "\t6 - Retirada de Livros" << endl;
        cout << "\t7 - Listagem de atrasos" << endl;
        cout << "\t8 - Historico de retirada" << endl;
        cout << "\t0 - Fim" << endl;
        cin >> escolha;
        cout << endl;
        cin.ignore();

        switch (escolha) {
        case 1:
            /*CADASTRO USUARIO*/
            cadastrousuario(users,usercont);
            break;
       
        case 2:
            cout << endl << "Escolha uma opcao:" << endl;
            cout << "\t1 - Cadastro dos Autores" << endl;
            cout << "\t2 - Cadastro das Editoras" << endl;
            cout << "\t3 - Cadastro de Livros" << endl;
            cout << "\t4 - Cadastro de Revistas" << endl;
            cout << "\t0 - Fim" << endl;
            cin >> escolha;
            cin.ignore();
/*CADASTROS DOS LIVROS E REVISTAS*/ switch (escolha) {
                            case 1:
                                cadastroautor(autor,autorcont);

                                
                                break;
                            case 2:
                                cadastroeditora(editora,editoracont);

                                
                                    break;
                                case 3:
                                    cadastrolivro(livros,autor,editora,livrocont);

                                    
                                    break;
                                case 4:
                                    cadastrorevista(revista,editora,revistacont);

                                   
                                    break;
                                case 0:
                                    break;
                                default:
                                    cout << "Opcao invalida, inserir numeros de 0 a 4" << endl;
                                }    
            break;
    

        case 3: 
            cout << endl << "Escolha uma opcao:" << endl;
            cout << "\t1 - Alterar dos Autores" << endl;
            cout << "\t2 - Alterar das Editoras" << endl;
            cout << "\t3 - Alterar de Livros" << endl;
            cout << "\t0 - Fim" << endl;
            cin >> escolha;
            cin.ignore();
            /*ALTERAR*/ switch (escolha) {
            case 1:
                alterarautor(autor);


                break;
            case 2:
                alterareditora(editora);


                break;
            case 3:
                alterarlivro(livros, autor, editora);
            case 0:
                break;
            default:
                cout << "Opcao invalida, inserir numeros de 0 a 3" << endl;
            
            }
            break;

        case 4:
       
            cout << endl << "Escolha uma opcao para a listagem:" << endl;
            cout << "\t1 - Listagem dos Autores" << endl;
            cout << "\t2 - Listagem das Editoras" << endl;
            cout << "\t3 - Listagem de Livros" << endl;
            cout << "\t4 - Listagem de Revistas" << endl;
            cout << "\t5 - Listagem dos Assuntos" << endl;
            cout << "\t0 - Fim" << endl;
            cin >> escolha;
            cin.ignore();
/*LISTAGEM DOS LIVROS E REVISTAS*/ switch (escolha) {
            case 1:
                listagemautores(autor);


                break;
            case 2:
                listagemeditora(livros,revista);


                break;
            case 3:
                listagemlivro(livros, autor, editora);


                break;
            case 4:

                listagemrevista(revista, editora);


                break;
            case 5: 
                listagemassuntos(livros, revista);
            case 0:
                break;
            default:
                cout << "Opcao invalida, inserir numeros de 0 a 5" << endl;
            }
           
         
            break;
        case 5:
            int opcoes;
            cout << endl << "Escolha uma opcao para listar para sua pesquisa:" << endl;
            cout << "\t1 - Titulo" << endl;
            cout << "\t2 - Autores" << endl;
            cout << "\t3 - Editoras" << endl;
            cout << "\t4 - Assunto" << endl;
            cout << "\t0 - Fim" << endl;
            cin >> opcoes;

            pesquisaritem(livros, revista, autor, editora, opcoes);

            break;
        case 6:
            retirarLivro(users, livros,autor,editora);

            break;

        case 7:
            listagematrasos(users,livros);
            
            break;
      

        
        case 8:
            historicaretirados(users,livros);
            break;
       

      
        case 0:
            break;
        default:
            cout << "Opcao invalida, inserir numeros de 0 a 5" << endl;
       }

    } while (escolha != 0);

   
    cout << "Volte sempre!" << endl;
    return 0;
}


