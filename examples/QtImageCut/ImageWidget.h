#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QImage>
#include <QRect>

class QPaintEvent;
class QMouseEvent;

class ImageWidget : public QWidget
{
public:
    ImageWidget();
    
    void setPixmap(const QString& path);
    void savePixmap(const QString& path);
    void autoSelect();
    
protected:
    virtual void paintEvent ( QPaintEvent * event );
    virtual void mouseMoveEvent ( QMouseEvent * event );
    virtual void mousePressEvent ( QMouseEvent * event );
    virtual void mouseReleaseEvent ( QMouseEvent * event );        
    
private:
    QImage m_pixmap;
    QRect m_rect;
    bool m_bDragMode;
};

#endif // IMAGEWIDGET_H
