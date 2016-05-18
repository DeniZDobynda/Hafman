#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>
#include "cryptonite.h"
#include <math.h>
//#include "divider.cpp"
#include <QFileDialog>
#include <QFile>

double entropy = 0;

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

/*

int Partition ( Cryptonite*& A, int left, int right)
{
    int x = A[left].count;

    int i = left - 1;

    for ( int j = left; j < right - 1; ++j)
    {
        if ( A[j].count <= x)
        {
            ++i;
            std::swap(A[i], A[j]);
        }


    }
    ++i;
    std::swap(A[i], A[right]);
    return i;
}


void quickSort ( Cryptonite*& A, int left, int right)
{
    if ( left >= right) return ;

    int i = Partition(A, left, right);
    quickSort(A, left, i-1);
    quickSort(A, i+1, right);

}

*/

void MainWindow::on_goCrypt_clicked()
{
    QString textToCrypt= ui->textToCrypt->document()->toPlainText();

    Cryptonite* string = new Cryptonite[textToCrypt.length()];

    int n = 0;                                                                  //lenth for new set with char and count

    for ( int i = 0; i < textToCrypt.length(); ++i) //go forward in text
    {
        QChar ch = textToCrypt.data()[i];                              //get one character

        int isExist = 0;                                                    //variable to know that i already had that character

        for ( int j = 0; string[j].count > 0; ++j )         //running in new set
        {
            if ( string[j].cha == ch   )                             //if my character exist
            {
                string[j].count++;                                     //plussing count
                isExist = 1;                                                 //ch exist!
            }
        }

        if ( !isExist )                                                         //if ch doesn't exist
        {
            string[n].cha = ch;                                           //then write a new one in a set
            string[n].count = 1;                                           //and start count with one
            n++;
        }

    }
    //here I have a set named "string" where is all symbols and their count

    if ( n > 2)
    {
        //quickSort(string, 0, n-1);                //sorting
    }else{
        if ( string[0].count < string[1].count)
        {
            Cryptonite temp;

            temp = string[0];

            string[0] = string[1];

            string[1] = temp;


        }
    }

    itemC *output = new itemC[n];

    //delete tree
    if ( t.head)
    {
        t.head = NULL;
    }

    Cryptonite* entrr = new Cryptonite[n];

    for ( unsigned short int i = 0; i < n; ++i) {entrr[i].count = string[i].count; entrr[i].cha = string[i].cha; }

    int k = 0;
    if ( n > 0)
    {
        if ( n != 1)
        t.push(string, n, "", output, k);                                               //////////////changed string

        else { t.push(string, n, "1", output, k);}
    }else{
        ui->textToDecrypt->setText("nothing to crypt)");

        return ;
    }

    out = k;

    QString result;
    for (int i = 0; i < textToCrypt.length(); ++i  )
    {
        int s = 0;
        while ( output[s].cha != textToCrypt.data()[i]) ++s;

        QString str = output[s].count;

        result.insert(result.length(), str);




    }

    int bit = result.length();

    // bit += bit % 8;

    // bit /= 8;

    ui->bit->setText(QString::number(bit));

    ui->textToDecrypt->setText(result);

    QString elemCodes = "";
    for ( unsigned int i = 0; i < k; ++i)
    {
        elemCodes.append(output[i].cha);
        elemCodes.append(" - ");
        elemCodes.append(output[i].count);
        elemCodes.append("\n");

    }

    ui->outputLabel->setText(elemCodes);


    ///enthropy
    ///
    ///
    double ent = 0;

    double everageLenght = 0;

    int m = textToCrypt.length();

    for ( unsigned int i = 0; i < n; ++i)
    {
        double p = (double)entrr[i].count / m;

        int s = 0;
        while ( output[s].cha != entrr[i].cha) ++s;

        everageLenght += p * output[s].count.length();

        ent += fabs(p*log2(p));
    }

    entropy = ent;

    QString ever = QString::number(everageLenght);

    ui->everageH->setText(ever);

    QString entr = QString::number(ent);

    ui->labelEnthropy->setText(entr);

    double effect = ent / everageLenght;

    QString eff = QString::number(effect);

    ui->effective->setText(eff);

}

void MainWindow::on_goDecrypt_clicked()
{
    if ( ui->textToDecrypt->document()->toPlainText() == NULL || !t.head)
    {
        ui->textToCryptCommon->setText("ERROR");

        return ;
    }

    else if ( !t.head->left && !t.head->right)
    {
        QString result = "";


        QString find = ui->textToDecrypt->document()->toPlainText();

        ui->textToDecrypt->clear();

        for ( int i = 0; i < find.length(); ++i )
        {
            if ( find.data()[i] != t.head->code.data()[0])
            {
                ui->textToCryptCommon->setText("ERROR");

                return ;
            }
            result.append(t.head->elems->cha);
        }

        ui->textToCryptCommon->setText(result);

        return ;
    }


    QString find = ui->textToDecrypt->document()->toPlainText();

    ui->textToDecrypt->clear();


    int i = 0;
    QString result;
    while ( i < find.length())
    {

        item* temp = t.head;

        while ( temp->left && i < find.length())                     //or temp.right
        {
            if ( find.data()[i].toLatin1() == '0')
            {
                temp = temp->left;
            }else if (find.data()[i].toLatin1() == '1')
            {
                temp = temp->right;
            }
            ++i;
        }
        if (temp->left && temp->right)
        {
            ui->textToCryptCommon->setText("ERROR");

            return ;
        }
        result.insert(result.length(), temp->elems->cha);
    }

    ui->textToCryptCommon->setText(result);
}

void MainWindow::on_goCryptH_clicked()
{

    QString textToCrypt = ui->textToCryptH->document()->toPlainText();

    ui->textToCryptH->clear();

    if ( textToCrypt == NULL || H.head == NULL)
    {
        ui->textToCryptHDefault->setText("Please, set default values");

        return ;
    }

    QString kkk = ui->textToCryptHDefault->document()->toPlainText();



    QString result = "";

    for ( int i = 0; i < textToCrypt.length(); ++i )
    {
        QChar ch;

        ch = textToCrypt.data()[i];

        unsigned short int founded = 0;

        for ( unsigned short int i = 0; i < kkk.length() && !founded; ++i )
        {
            if ( ch == kkk.data()[i] )
            {
                founded = 1;
            }
        }

        if ( !founded)
        {
            ui->textToDectyptH->setText("ERROR");

            return ;
        }

        QString temp;

        temp = H.getCode(ch);

        result.append(temp);

    }

    ui->textToDectyptH->setText(result);
}

void MainWindow::on_goDecryptH_clicked()
{
    if ( ui->textToDectyptH->document()->toPlainText() == NULL) return ;

    QString qstr;

    qstr = H.decode(ui->textToDectyptH->document()->toPlainText());

    ui->textToDectyptH->clear();

    if ( qstr.data()[0] == 'N')
    {
        ui->textToCryptH->setText("ERROR");

        return ;
    }

    ui->textToCryptH->setText(qstr);
}

void MainWindow::on_goCrypt_2_clicked()
{
    QString result;

    QString textToCrypt = ui->textToCryptCommon->document()->toPlainText();

    ui->textToCryptCommon->clear();

    itemC *output;

    output = t.result;
    for (int i = 0; i < textToCrypt.length(); ++i  )
    {
        int s = 0;
        while ( output[s].cha != textToCrypt.data()[i]) ++s;

        if ( s >= out)
        {
            ui->textToDecrypt->setText("ERROR");

            return ;
        }

        QString str = output[s].count;

        result.insert(result.length(), str);




    }

    ui->textToDecrypt->setText(result);
}

void MainWindow::on_pushButton_clicked()
{
    QString textToCrypt = ui->textToCryptHDefault->document()->toPlainText();

    this->H = hafman(textToCrypt);

    QString result = "";

    for ( int i = 0; i < textToCrypt.length(); ++i )
    {
        QChar ch;

        ch = textToCrypt.data()[i];

        QString temp;

        temp = H.getCode(ch);

        result.append(temp);

    }

    int bit = result.length();

    //  bit += bit % 8;

    // bit /= 8;

    ui->bitH->setText(QString::number(bit));

    ui->textToDectyptH->setText(result);

    ui->outputHLabel->setText(H.getCodes());

    double everage = 0;

    double ent = 0;

    int m = textToCrypt.length();

    for ( int i = 0; i <= H.count; ++i)
    {
        double p = double(H.elems[i]->count) / m;

        everage += p*H.getCode(H.elems[i]->ch).length();

        ent += fabs(p*log2(p));
    }

    double effect = ent / everage;

    QString eff = QString::number(effect);

    ui->effectiveH->setText(eff);

    QString ever = QString::number(everage);

    ui->everage->setText(ever);

    QString entropy = QString::number(ent);

    ui->labelEnthropyH->setText(entropy);
}

void MainWindow::on_pushButton_2_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Text"), "/Users/Denis/Desktop", tr("Text Files (*.txt)"));

    if ( fileName == NULL) return ;

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QByteArray bite = file.readLine();

    QString line = bite.data();

    ui->textToCrypt->setText(line);

    ui->textToCryptHDefault->setText(line);

    on_goCrypt_clicked();

    on_pushButton_clicked();


}

void MainWindow::on_actionOpen_File_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Text"), "/Users/Denis/Desktop", tr("Text Files (*.txt)"));

    if ( fileName == NULL) return ;

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;


    QByteArray bite = file.readLine();

    file.close();

    QString line = bite.data();

    ui->textToCrypt->setText(line);

    ui->textToCryptHDefault->setText(line);

    on_goCrypt_clicked();

    on_pushButton_clicked();

}

void MainWindow::on_actionABC_triggered()
{
    ui->textToCrypt->setText("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890 !@#$%^&*()_+-/\|~`");

    ui->textToCryptHDefault->setText("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890 !@#$%^&*()_+-/\|~`");

    on_goCrypt_clicked();

    on_pushButton_clicked();
}

void MainWindow::on_actionRandom_triggered()
{
    int n = abs(qrand()%20)+50;

    QString line = "";

    for ( unsigned short int i = 0; i < n; ++i )
    {
        line.append(qrand()%50+35);
    }

    ui->textToCrypt->setText(line);

    ui->textToCryptHDefault->setText(line);

    on_goCrypt_clicked();

    on_pushButton_clicked();
}

void MainWindow::on_actionCode_from_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Text"), "/Users/Denis/Desktop", tr("Text Files (*.txt)"));

    if ( fileName == NULL) return ;

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QByteArray bite = file.readLine();

    file.close();

    QString line = bite.data();

    ui->textToCryptCommon->setText(line);

    ui->textToCryptH->setText(line);

    on_goCrypt_2_clicked();

    on_goCryptH_clicked();


    ui->textToCryptCommon->setText(line);

    ui->textToCryptH->setText(line);

}

void MainWindow::on_actionDecode_from_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Text"), "/Users/Denis/Desktop", tr("Text Files (*.txt)"));

    if ( fileName == NULL) return ;

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QByteArray bite = file.readLine();

    file.close();

    QString line = bite.data();

    ui->textToDecrypt->setText(line);

    ui->textToDectyptH->setText(line);

    on_goDecrypt_clicked();

    on_goDecryptH_clicked();

    ui->textToDecrypt->setText(line);

    ui->textToDectyptH->setText(line);

}

void MainWindow::on_actionSave_all_to_file_triggered()
{
    QString fileName = QFileDialog::getSaveFileName();

    if ( fileName == NULL) return ;

    QFile file(fileName);

    file.open(QIODevice::WriteOnly);

    //if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    //  return;

    file.putChar(10);
    file.putChar(13);

    if ( ui->textToCrypt->document()->toPlainText() != NULL)
    {

        file.putChar(10);
        file.putChar(13);
        file.write("-->>the Base of Shenon-Fano");

        file.putChar(10);
        file.putChar(13);
        file.write(ui->textToCrypt->document()->toPlainText().toLatin1().data());
    }

    if ( ui->textToCryptCommon->document()->toPlainText() != NULL)
    {
        file.putChar(10);
        file.putChar(13);
        file.write("-->>Text to crypt Shenon-Fano");
        file.putChar(10);
        file.putChar(13);
        file.write(ui->textToCryptCommon->document()->toPlainText().toLatin1().data());
    }

    if ( ui->textToDecrypt->document()->toPlainText() != NULL)
    {
        file.putChar(10);
        file.putChar(13);
        file.write("-->>Text to decrypt Shenon-Fano");
        file.putChar(10);
        file.putChar(13);
        file.write(ui->textToDecrypt->document()->toPlainText().toLatin1().data());
    }


    if ( ui->textToCryptHDefault->document()->toPlainText() != NULL)
    {
        file.putChar(10);
        file.putChar(13);
        file.putChar(10);
        file.putChar(13);
        file.write("-->>the Base of Hafman");
        file.putChar(10);
        file.putChar(13);
        file.write(ui->textToCryptHDefault->document()->toPlainText().toLatin1().data());
    }

    if ( ui->textToCryptH->document()->toPlainText() != NULL)
    {
        file.putChar(10);
        file.putChar(13);
        file.write("-->>Text to crypt Hafman");
        file.putChar(10);
        file.putChar(13);
        file.write(ui->textToCryptH->document()->toPlainText().toLatin1().data());
    }

    if ( ui->textToDectyptH->document()->toPlainText() != NULL)
    {
        file.putChar(10);
        file.putChar(13);
        file.write("-->>Text to decrypt Hafman");
        file.putChar(10);
        file.putChar(13);
        file.write(ui->textToDectyptH->document()->toPlainText().toLatin1().data());
    }

    file.close();

}
