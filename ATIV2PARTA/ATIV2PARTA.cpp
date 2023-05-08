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
    bool Retirado=false;
  
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
struct tm Datadevolucao;

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
void cadastroautor(Autor autor[], int &contautores) {
    Autor autores;
    
    while (true) {
        if (contautores >= maxautor) {
            cout << "Número máximo de autores atingido." << endl;
            break;
        }

        cout << "Digite o nome do autor "<< contautores <<":" << endl;
        cin >> autor[contautores].Nome;

        contautores++;

        cout << "Deseja cadastrar mais um autor? (s/n): ";
        char opcao;
        cin >> opcao;
        if (opcao == 'n' || opcao == 'N') {
            break;
        }
    }

    cout << "Autores cadastrados:" << endl;
    for (int i = 0; i < contautores; i++) {
        cout << i + 1 << ". " << autor[i].Nome << endl;
    }
}
void alterarAutor(Autor autores[]) {
    int opcao;
    cout << "Selecione o autor que deseja alterar: " << endl;
    for (int i = 0; i < maxautor; i++) {
        cout << i << ". " << autores[i].Nome << endl;
    }
    cin >> opcao;

    // verifica se a opção escolhida é válida
    if (opcao < 0 || opcao >= maxautor) {
        cout << "Opção inválida." << endl;
        return;
    }

    // pede ao usuário para digitar o novo nome do autor
    cout << "Digite o novo nome do autor: ";
    cin >> autores[opcao].Nome;

    cout << "Autor alterado com sucesso!" << endl;
}

/*CADASTRAR E ALTERAR EDITORA*/
void cadastroeditora(Editora editor[], int &conteditor) {
    Editora editores;
    
    while (true) {
        if (conteditor >= maxeditora) {
            cout << "Número máximo de Editoras atingido." << endl;
            break;
        }

        cout << "Digite o nome da Editora " << conteditor << ":" << endl;
        cin >> editor[conteditor].Nome;

        conteditor++;

        cout << "Deseja cadastrar mais uma Editora? (s/n): ";
        char opcao;
        cin >> opcao;
        if (opcao == 'n' || opcao == 'N') {
            break;
        }
    }

    cout << "Editoras cadastradas:" << endl;
    for (int i = 0; i < conteditor; i++) {
        cout << i + 1 << ". " << editor[i].Nome << endl;
    }
}
void alterareditora(Autor autores[]) {
    int opcao;
    cout << "Selecione o autor que deseja alterar: " << endl;
    for (int i = 0; i < maxautor; i++) {
        cout << i << ". " << autores[i].Nome << endl;
    }
    cin >> opcao;

    // verifica se a opção escolhida é válida
    if (opcao < 0 || opcao >= maxautor) {
        cout << "Opção inválida." << endl;
        return;
    }

    // pede ao usuário para digitar o novo nome do autor
    cout << "Digite o novo nome do autor: ";
    cin >> autores[opcao].Nome;

    cout << "Autor alterado com sucesso!" << endl;
}

/*CADASTRO USUARIO*/
void cadastrousuario(Usuario users[], int &i ) {
    int continuar = 1;
    do {
        // Pede ao usuário para digitar o código

        int id;
        
        do {
            cout << "Usuario " << i << ":" << endl;
            cout << "Digite um código de 5 dígitos (1 a 9): ";
            cin >> id;
        } while (id < 11111 || id > 99999); // verifica se o código tem 5 dígitos e está no intervalo [11111, 99999]

        // Verifica se o código já existe
        bool existe = false;
        for (int j = 0; j < i; j++) {

            if (users[j].Id == id) { // aqui deve ser users[j] em vez de users[i]

                existe = true;
                break;
            }
        }
        if (existe) {
            cout << "Esse código já foi cadastrado. Tente novamente.\n";
            continue; // repete a iteração para pedir um novo código
        }

        // Pede ao usuário para digitar o nome

        cout << "Digite um nome (sem números): ";
        cin.ignore();
        getline(cin, users[i].Nome);
        users[i].Id = id; // adiciona o código ao usuário cadastrado
        i++;

        cout << "Deseja sair? precione 1 para nao e 0 para sim: ";
        cin >> continuar;
    } while (continuar != 0);
}


/*CADASTRAR LIVRO*/
void cadastrolivro(Livro livros[], Autor autores[], Editora editoras[], int &contlivro) {
    Livro opcaoautor;
    
    bool continuar = true;

    while (continuar) {
        cout << "Digite o título do livro " << contlivro << ":" << endl;
        cin.ignore();
        getline(cin, livros[contlivro].Titulo);

        cout << "Digite o assunto do livro: ";
        getline(cin, livros[contlivro].Assunto);

        // Mostra a lista de autores cadastrados
        cout << "Autores cadastrados:\n";
        for (int j = 0; j < maxautor; j++) {
            cout << j << ". " << autores[j].Nome << endl;
        }

        // Pede ao usuário para escolher um autor
        int opcao;
        do {
            cout << "Digite o número do autor: ";
            cin >> opcao;
        } while (opcao < -1 || opcao >= maxautor); // verifica se a opção é válida

        livros[contlivro].Autor = autores[opcao];
        /////////////////////////////////////////////////////////////////////////////////////////////
                // Mostra a lista de editoras cadastradas
        cout << "Editoras cadastradas:\n";
        for (int j = 0; j < maxeditora; j++) {
            cout << j << ". " << editoras[j].Nome << endl;
        }


        // Pede ao usuário para escolher uma editora ou cadastrar uma nova
        do {
            cout << "Digite o número da editora: ";
            cin >> opcao;
        } while (opcao < -1 || opcao >= maxeditora); // verifica se a opção é válida


        // Usa uma editora já cadastrada
        livros[contlivro].Editora = editoras[opcao];


        ///////////////////////////////////////////////////////////////////////////////////////////////////
        srand(time(NULL));
        livros[contlivro].Id = rand() % 100000; // gera um número aleatório entre 0 e 99999
        livros[contlivro].Id = livros[contlivro].Id + 10000; // adiciona 10000 para garantir que o código tenha 5 dígitos
        livros[contlivro].Id = livros[contlivro].Id % 100000; // remove o primeiro dígito (caso o código gerado seja maior do que 99999)
        if (livros[contlivro].Id < 10000) {
            livros[contlivro].Id = livros[contlivro].Id + 10000; // adiciona 10000 novamente, caso o código tenha menos de 5 dígitos
        }
        cout << "O código gerado para este livro é: " << livros[contlivro].Id << endl;
        contlivro++;

        // Pergunta ao usuário se deseja continuar cadastrando livros
        char resposta;
        do {
            cout << "Deseja cadastrar outro livro? (S/N) ";
            cin >> resposta;
        } while (resposta != 'S' && resposta != 's' && resposta != 'N' && resposta != 'n');

        if (resposta == 'N' || resposta == 'n') {
            continuar = false;
        }
    }

    cout << "Cadastro de livros finalizado." << endl;
}
void alterarLivro(Livro livros[], Autor autores[], Editora editoras[]) {
    int opcao;
    cout << "Selecione o livro que deseja alterar: " << endl;
    for (int i = 0; i < maxlivros; i++) {
        cout << i << ". " << livros[i].Titulo << endl;
    }
    cin >> opcao;

    // verifica se a opção escolhida é válida
    if (opcao < 0 || opcao >= maxlivros) {
        cout << "Opção inválida." << endl;
        return;
    }

    // pede ao usuário para digitar as novas informações do livro
    cout << "Digite o novo título do livro: ";
    getline(cin, livros[opcao].Titulo);

    cout << "Digite o novo assunto do livro: ";
    getline(cin, livros[opcao].Assunto);

    // verifica se o autor existe e atualiza o valor correspondente no array de livros
    int opcaoAutor;
    cout << "Selecione o autor do livro: " << endl;
    for (int i = 0; i < maxautor; i++) {
        cout << i << ". " << autores[i].Nome << endl;
    }
    cin >> opcaoAutor;

    if (opcaoAutor < 0 || opcaoAutor >= maxautor) {
        cout << "Autor inválido." << endl;
        return;
    }

    livros[opcao].Autor = autores[opcaoAutor];

    // verifica se a editora existe e atualiza o valor correspondente no array de livros
    int opcaoEditora;
    cout << "Selecione a editora do livro: " << endl;
    for (int i = 0; i < maxeditora; i++) {
        cout << i << ". " << editoras[i].Nome << endl;
    }
    cin >> opcaoEditora;

    if (opcaoEditora < 0 || opcaoEditora >= maxeditora) {
        cout << "Editora inválida." << endl;
        return;
    }

    livros[opcao].Editora = editoras[opcaoEditora];

    cout << "Livro alterado com sucesso!" << endl;
}


/*CADASTRAR REVISTA*/
void cadastrorevista(Revista rev[], Editora edit[], int &i) {
   

    do {
        cout << "Digite o título da Revista " << i << ":" << endl;
        getline(cin, rev[i].Titulo);

        cout << "Digite o assunto da Revista: ";
        getline(cin, rev[i].Assunto);

        // Mostra a lista de editoras cadastradas
        cout << "Editoras cadastradas:\n";
        for (int j = 0; j < maxeditora; j++) {
            cout << j << ". " << edit[j].Nome << endl;
        }

        // Pede ao usuário para escolher uma editora ou cadastrar uma nova
        int opcao;
        do {
            cout << "Digite o número da editora: ";
            cin >> opcao;
        } while (opcao < -1 || opcao >= maxeditora); // verifica se a opção é válida

        rev[i].Editora = edit[opcao];
        i++;

        // Pergunta ao usuário se deseja cadastrar mais uma revista
        cout << "Deseja cadastrar mais uma revista? (s/n): ";
        char opcoes;
        cin >> opcoes;
        cin.ignore(); // Limpa o buffer do teclado

        if (opcoes == 'n' || opcoes == 'N' || i >= maxrevistas) {
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

    // Pedir ID do usuário
    cout << "Digite seu ID: ";
    cin >> idUser;

    // Encontrar usuário
    for (int i = 0; i < maxusers; i++) {
        if (users[i].Id == idUser) {
            userEncontrado = true;
            break;
        }
    }

    if (!userEncontrado) {
        cout << "Usuário não encontrado!" << endl;
        return;
    }

    cout << "Livros disponíveis para retirada:" << endl;
    for (int i = 0; i < maxlivros; i++) {
        if (livros[i].Retirado == false) {
            cout << livros[i].Id << ". " << livros[i].Titulo << " - " << endl;
        }
    }

    // Pede ao usuário para escolher o ID do livro a ser retirado
    do {
        cout << "Digite o ID do livro que deseja retirar: ";
        cin >> idLivro;

        // Procura o livro com o ID escolhido pelo usuário
        for (int i = 0; i < maxlivros; i++) {
            if (livros[i].Id == idLivro) {
                livroEncontrado = true;

                // Verifica se o livro está disponível para empréstimo
                if (livros[i].Retirado == true) {
                    cout << "Este livro já foi retirado por outro usuário." << endl;
                    livroEncontrado = false;
                    break;
                }

                // Registra o empréstimo
                livros[i].Retirado = true;
                livros[i].IDuser = idUser;
                cout << "Livro " << livros[i].Titulo << " retirado com sucesso!" << endl;
                break;
            }
        }

        if (!livroEncontrado) {
            cout << "Livro não encontrado. Tente novamente." << endl;
        }
    } while (!livroEncontrado);

    cout << "Livro escolhido: " << livro.Titulo << endl;

    // Calcula a data de devolução (7 dias após a data atual)
    time_t agora = time(0);
    
    localtime_s(&Datadevolucao, &agora);
    Datadevolucao.tm_mday += 7;
    mktime(&Datadevolucao); //Converts tm structure to time_t format or calendar equivalent.
    cout << "Livro retirado com sucesso. Por favor, devolva até " << Datadevolucao.tm_mday << "/" << Datadevolucao.tm_mon + 1 << "/" << Datadevolucao.tm_year + 1900 << endl;
    return;
    
}

void listagematrasos(Usuario users[], Livro livros[]) {
    Usuario user;
    int userID;
    bool livroEncontrado = false;
    bool userEncontrado = false;

    // Obter a data e hora atuais
    time_t agora = time(0);

    // Pedir ID do usuário
    cout << "Digite seu ID: ";
    cin >> userID;

    // Encontrar usuário
    for (int i = 0; i < maxusers; i++) {
        if (users[i].Id == userID) {
            userEncontrado = true;
            break;
        }
    }

    if (!userEncontrado) {
        cout << "Usuário não encontrado!" << endl;
        return;
    }

    // Mostrar os livros emprestados pelo usuário que estão atrasados
    bool temLivroAtrasado = false;
    for (int i = 0; i < maxlivros; i++) {
        Livro livro = livros[i];
        if (Datadevolucao.tm_mday != 0 && Datadevolucao.tm_mday < agora && livro.IDuser == userID) {
            if (!temLivroAtrasado) {
                cout << "Os seguintes livros estão atrasados:\n";
                temLivroAtrasado = true;
            }
            cout << livro.Titulo << "\n";
        }
    }

    // Se não há livros atrasados, mostrar uma mensagem
    if (!temLivroAtrasado) {
        cout << "Não há livros atrasados para o usuário: " << userID << "\n";
    }
}

void historicaretirados(Usuario users[], Livro livros[]) {
    int idUser;
    bool userEncontrado = false;

    // Pedir o ID do usuário
    do {
        cout << "Digite o ID do usuário para ver o histórico de retiradas: ";
        cin >> idUser;
    } while (idUser < 11111 || idUser > 99999); // verifica se o ID tem 5 dígitos e está no intervalo [11111, 99999]

    // Verificar se o usuário existe
    for (int i = 0; i < maxusers; i++) {
        if (users[i].Id == idUser) {
            userEncontrado = true;
            break;
        }
    }

    if (!userEncontrado) {
        cout << "Usuário não encontrado." << endl;
        return;
    }

    Livro livrosRetirados[maxlivros];
    int numret = 0;

    // Filtrar livros retirados pelo usuário
    for (int i = 0; i < maxlivros; i++) {
        if (livros[i].Retirado && livros[i].IDuser == idUser) {
            livrosRetirados[numret] = livros[i];
            numret++;
        }
    }

    if (numret == 0) {
        cout << "O usuário não tem livros emprestados." << endl;
    }
    else {
        cout << "Histórico de empréstimos do usuário:" << endl;
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
        cout << "Nome das Editoras das dos livros: " << livros[i].Editora.Nome << endl;
    }
    for (int i = 0; i < maxrevistas; i++) {
        cout << "Nome das Editoras das revistas: " << rev[i].Editora.Nome << endl;
    }
};
void listagemlivro(Livro livros[], Autor autor[], Editora edit[]) {
    cout << "Lista de Livros" << endl;
    for (int i = 0; i < maxlivros; i++) {
        cout << "ID: " << livros[i].Id << endl;
        cout << "Titulo: " << livros[i].Titulo << endl;
        cout << "Assunto: " << livros[i].Assunto << endl;
        cout << "Autor: " << livros[i].Autor.Nome << endl;
        cout << "Editora: " << livros[i].Editora.Nome << endl;


    }
};
void listagemrevista(Revista rev[], Editora edit[]) {
    cout << "Lista das Revistas" << endl;
    for (int i = 0; i < maxrevistas; i++) {
        cout << "Titulo: " << rev[i].Titulo << endl;
        cout << "Assunto: " << rev[i].Assunto << endl << endl;
        cout << "Editora: " << rev[i].Editora.Nome << endl;


    }
};
void listagemassuntos(Livro livros[], Revista rev[]) {
    cout << "Lista dos Assuntos" << endl;
    for (int i = 0; i < maxlivros; i++) {
        cout << "Assuntos dos livros: " << livros[i].Assunto << endl;
    }
    for (int i = 0; i < maxrevistas; i++) {
        cout << "Assuntos das revistas: " << rev[i].Assunto << endl;
    }
};

int main()
{
    setlocale(LC_ALL, "Portuguese");
    Livro livros[maxlivros];
    Revista revista[maxrevistas];
    Autor autor[maxautor];
    Editora editora[maxeditora];
    Usuario users[maxusers];
    int escolha;
    int usercont = 4;
    int livrocont = 4;
    int revistacont = 4;
    int autorcont = 4;
    int editoracont = 4;


    do {
        cout << endl << "Escolha uma opcao:" << endl;
        cout << "\t1 - Cadastro dos usuarios" << endl;
        cout << "\t2 - Cadastro para livros e Revistas e afins" << endl;
        cout << "\t3 - Listagem de Livros e Revistas e afins" << endl;
        cout << "\t4 - Retirada de Livros" << endl;
        cout << "\t5 - Listagem de atrasos" << endl;
        cout << "\t6 - Historico de retirada" << endl;
        cout << "\t0 - Fim" << endl;
        cin >> escolha;
        cout << endl;
        cin.ignore();

        switch (escolha) {
        case 1:
            /*CADASTRO USUARIO*/
            cadastrousuario(users,usercont);
            break;
 /////////////////////////////////////////////////////////////////////       
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
    
///////////////////////////////////////////////////////////////////////////////////
       
        case 3:
       
            cout << endl << "Escolha uma opcao:" << endl;
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
        case 4:
            retirarLivro(users, livros,autor,editora);

            break;
///////////////////////////////////////////////////////////////////////////////////
        case 5:
            listagematrasos(users,livros);
            
            break;
      
 //////////////////////////////////////////////////////////////////////////////////
        
        case 6:
            historicaretirados(users,livros);
            break;
       
////////////////////////////////////////////////////////////////////////////////////
      
        case 0:
            break;
        default:
            cout << "Opcao invalida, inserir numeros de 0 a 5" << endl;
       }

    } while (escolha != 0);

   

}


