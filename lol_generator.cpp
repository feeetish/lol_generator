#include "lol_generator.h"
#include <stdio.h>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QTextCodec>
#include <QSizePolicy>
#include <ctime>
using namespace std;

lol_generator::lol_generator(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	ui.player_result_tablewidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.player_result_tablewidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.player_result_tablewidget->verticalHeader()->setHidden(true);
	m_area_layout = new QGridLayout;
	ui.player_pool_area->setLayout(m_area_layout);
	m_area_layout->setSpacing(0);
	m_area_layout->setMargin(0);
	QStringList strs;
	strs <<QStringLiteral("蓝色方")<<QStringLiteral("红色方");
	ui.player_result_tablewidget->setHorizontalHeaderLabels(strs);
	connect(ui.import_txt_pushbutton,SIGNAL(clicked()),this,SLOT(ImportPlayersFromTxt()));
	connect(ui.start_roll_pushButton,SIGNAL(clicked()),this,SLOT(RollPlayers()));

	m_players_pool.clear();
	m_players_lst.clear();

}

lol_generator::~lol_generator()
{

}

void lol_generator::ImportPlayersFromTxt()
{
	QString fileName = QFileDialog::getOpenFileName(this,QStringLiteral("选择选手文件"),"C:",QStringLiteral("文本文件(*txt)"));
	QByteArray line;
	QString str;
	ui.player_result_tablewidget->clearContents();

	QFile player_txt_file(fileName);
	if (!player_txt_file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QMessageBox::information(this,QStringLiteral("错误"),QStringLiteral("文件打不开"));
		return;
	}
	while (!player_txt_file.atEnd())
	{
		line = player_txt_file.readLine();
		str = line;
		m_players_lst.append(str);
		//m_players_pool.insert(str);
	}

	/*for(int i = 0;i < m_players_lst.size() && i < 10;i++)
	{
		ui.player_result_tablewidget->setItem(i/2,i%2,new QTableWidgetItem(m_players_lst.at(i)));
	}*/
	FullPlayerPoolWithButoon();
}

void lol_generator::SlotPlayerButtonClicked()
{
	QPushButton *btn = (QPushButton*)sender();
	if (btn->isChecked() && m_players_pool.size()<10)
	{
		m_players_pool.insert(btn->text());
	}
	else
	{
		m_players_pool.remove(btn->text());
	}
	UpdatePlayerTable();

}

void lol_generator::UpdatePlayerTable()
{
	ui.player_result_tablewidget->clearContents();
	QList<QString> pool_lst = m_players_pool.toList();
	for(int i = 0;i < pool_lst.size() && i < 10;i++)
	{
		ui.player_result_tablewidget->setItem(i/2,i%2,new QTableWidgetItem(pool_lst.at(i)));
	}
}

void lol_generator::FullPlayerPoolWithButoon()
{
	/*m_area_layout = new QGridLayout;
	ui.player_pool_area->setLayout(m_area_layout);
	m_area_layout->setSpacing(0);
	m_area_layout->setMargin(0);*/

	for(int i = 0;i < m_players_lst.size();i++)
	{
		QPushButton *btn = new QPushButton(m_players_lst.at(i),ui.player_pool_area);
		m_area_layout->addWidget(btn,i%4,i/4,Qt::AlignLeft);
		QSizePolicy size_policy = btn->sizePolicy();
		size_policy.setHorizontalPolicy(QSizePolicy::Fixed);
		size_policy.setVerticalPolicy(QSizePolicy::Fixed);
		btn->setSizePolicy(size_policy);
		btn->setCheckable(true);
		connect(btn,SIGNAL(clicked()),this,SLOT(SlotPlayerButtonClicked()));

	}
}

void lol_generator::SlotTest()
{
	int a =0;
	return;
}

void lol_generator::RollPlayers()
{
	ui.player_result_tablewidget->clearContents();
	QList<QString> tmp_list = m_players_pool.toList();
	QList<QString> blue_list,red_list;

	srand((unsigned)time(NULL));
	int index = 0;
	int size = tmp_list.size()/2;
	for (int i = 0;i<size;i++)
	{
		index = rand()%tmp_list.length();
		red_list.append(tmp_list.at(index));
		tmp_list.removeAt(index);
	}
	blue_list = tmp_list;
	
	for(int i = 0;i < blue_list.size() && i < 5;i++)
	{
		ui.player_result_tablewidget->setItem(i,0,new QTableWidgetItem(blue_list.at(i)));
	}
	for(int i = 0;i < red_list.size() && i < 5;i++)
	{
		ui.player_result_tablewidget->setItem(i,1,new QTableWidgetItem(red_list.at(i)));
	}
}