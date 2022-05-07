#ifndef LOL_GENERATOR_H
#define LOL_GENERATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_lol_generator.h"

class lol_generator : public QMainWindow
{
	Q_OBJECT

public:
	lol_generator(QWidget *parent = 0);
	~lol_generator();

	void FullPlayerPoolWithButoon();
	void UpdatePlayerTable();
private slots:
	void ImportPlayersFromTxt();
	void SlotPlayerButtonClicked();
	void SlotTest();
	void RollPlayers();
	
private:
	Ui::lol_generatorClass ui;
	QSet<QString> m_players_pool;
	QList<QString> m_players_lst;
	QGridLayout *m_area_layout;

};

#endif // LOL_GENERATOR_H
