#ifndef PREVIOUSWEEKWIDGET_H
#define PREVIOUSWEEKWIDGET_H

#include <QWidget>
#include "tablemodels.h"
namespace Ui {
class PreviousWeekWidget;
}

class PreviousWeekWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PreviousWeekWidget(QWidget *parent = 0);
    ~PreviousWeekWidget();
    void setWeekData(int week);
    int weekNumber() { return myWeekNumber; }

private:
    Ui::PreviousWeekWidget *ui;
    int myWeekNumber = -1;
    GameTableModel  myGameTableModel{WeekDisplayType::PreviousWeek};    
    ProjectionSheetTableModel myProjectionsModel {WeekDisplayType::PreviousWeek};
    QItemSelectionModel myGamesSelectionModel;
    QScopedPointer<ProjectionsViewFilterProxyModel> myProjectionFilterProxy;
    int myCurrentWeek;
    std::vector<GameResult> myGamesResults;
    fantasybit::WeeklySchedule myWeeklySchedule;
    void invalidateFilters();

};

#endif // PREVIOUSWEEKWIDGET_H