#ifndef CNOTE_H
#define CNOTE_H

#include <QWidget>
#include <QtGui>
#include <QDialog>
#include <qtextedit.h>
#include <QLabel>

class Cnote : public QDialog
{
    Q_OBJECT
public:
    explicit Cnote(QWidget *parent = 0);
    ~Cnote();
    QPixmap pix;
    void paintEvent(QPaintEvent *);
    QPoint dragPos;
    QTextEdit *textedit;
    QLabel *datelabel;
protected:
    void  mouseMoveEvent(QMouseEvent *event);
    void  mousePressEvent(QMouseEvent *event);
    void  mouseReleaseEvent(QMouseEvent *event);
private:
    QPushButton *ok;
    QPushButton *cancel;
    QPushButton *clearplan;
public slots:
    void savenote();
    void cancelnote();
    void clean();

signals:
    void save(QString);
    void setPlan(bool bFlag);
};

#endif // CNOTE_H
