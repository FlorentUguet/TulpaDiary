#include "tulpawidget.h"

TulpaWidget::TulpaWidget(QWidget *parent) : QWidget(parent)
{ 
    outputInfo(L_DEBUG,"Loading Tulpas Widget");

    mainlayout = new QVBoxLayout;
    comboBoxTulpa = new QComboBox(this);

    loadTulpas();

    groupBoxInfos = new QGroupBox("Infos",this);
    QVBoxLayout *layoutInfos = new QVBoxLayout;
    labelsInfo[TULPA_BIRTH] = new QLabel(this);
    labelsInfo[TULPA_FIRST_WORD] = new QLabel(this);
    layoutInfos->addWidget(labelsInfo[TULPA_BIRTH]);
    layoutInfos->addWidget(labelsInfo[TULPA_FIRST_WORD]);
    groupBoxInfos->setLayout(layoutInfos);

    personalityModel = new QStringListModel(personalityList);
    personalityView = new QListView(this);
    personalityView->setModel(personalityModel);

    sessionsModel = new QStringListModel(sessionsList);
    sessionsView = new QListView(this);
    sessionsView->setModel(sessionsModel);

    QHBoxLayout *layoutTop = new QHBoxLayout;
    QPushButton *pBEdit = new QPushButton("Edit",this);
    QPushButton *pBAdd = new QPushButton("Add",this);
    layoutTop->addWidget(comboBoxTulpa,8);
    layoutTop->addWidget(pBEdit);
    layoutTop->addWidget(pBAdd);

    mainlayout->addLayout(layoutTop);
    mainlayout->addWidget(groupBoxInfos);
    mainlayout->addWidget(personalityView);
    mainlayout->addWidget(sessionsView);

    setLayout(mainlayout);

    connect(comboBoxTulpa,SIGNAL(currentIndexChanged(QString)),this,SLOT(loadTulpa(QString)));
    connect(pBAdd,SIGNAL(clicked()),this,SLOT(addTulpa()));
    connect(pBEdit,SIGNAL(clicked()),this,SLOT(editTulpa()));

    loadTulpa(comboBoxTulpa->currentText());
}

TulpaWidget::~TulpaWidget()
{

}

void TulpaWidget::loadTulpas()
{
    comboBoxTulpa->clear();

    QDir tulpadir(TULPA_FOLDER);
    tulpadir.setFilter(QDir::Files | QDir::NoDotAndDotDot);

    QString buffer;
    int entry_size = tulpadir.entryList().size();
    qDebug() << entry_size << "entries";

    for(int i=0;i<entry_size;i++)
    {
        qDebug() << tulpadir.entryInfoList().at(i).absoluteFilePath();
        if (tulpadir.entryInfoList().at(i).baseName().isEmpty())
        {

        }
        else
        {
            buffer = tulpadir.entryInfoList().at(i).baseName();
            buffer[0] = buffer[0].toUpper();
            comboBoxTulpa->addItem(buffer);

            outputInfo(L_DEBUG,"Loaded Tulpa " + buffer.toStdString());
        }

    }
}

void TulpaWidget::addTulpa()
{
    AddTulpaWidget *w = new AddTulpaWidget(0);
    w->show();
    connect(w,SIGNAL(finished()),this,SLOT(reload()));
}

void TulpaWidget::editTulpa()
{
    AddTulpaWidget *w = new AddTulpaWidget(comboBoxTulpa->currentText(),0);
    w->show();
    connect(w,SIGNAL(finished()),this,SLOT(reload()));
}

void TulpaWidget::reload()
{
    loadTulpas();
    //comboBoxTulpa->setCurrentIndex(0);
    loadTulpa(comboBoxTulpa->currentText());
}

void TulpaWidget::loadTulpa(QString name)
{
    tulpa.loadByName(name.toStdString());

    loadInfos();
    loadPersonality();
    loadSessions();
}

void TulpaWidget::loadInfos()
{
    labelsInfo[TULPA_BIRTH]->setText(QString("Birth : ") + QString(tulpa.getBirthTime().c_str()));

    labelsInfo[TULPA_FIRST_WORD]->setText(QString("First Word : ") + QString(tulpa.getFirstWordTime().c_str()));

}

void TulpaWidget::loadPersonality()
{
    personalityList.clear();
    personalityList.push_back(QString("Personality :"));

    for(int i=0;i<tulpa.getPersonalityTraits().size();i++)
    {
        personalityList.push_back(QString("  -") + QString(tulpa.getPersonalityTrait(i).c_str()));
    }

    personalityModel->setStringList(personalityList);
}

void TulpaWidget::loadSessions()
{
    Session session_buffer;

    sessionsList.clear();
    sessionsList.push_back(QString("Sessions :"));

    for(int i=0;i<tulpa.getSessions().size();i++)
    {
        sessionsList.push_back(QString("  -") +QString::number(session_buffer.getId()));
    }


    sessionsModel->setStringList(sessionsList);
}

void TulpaWidget::clearLayout(QLayout *layout)
{
    if(layout != NULL)
    {
        QLayoutItem* item;
        while ( ( item = layout->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
        delete layout;
    }
}

