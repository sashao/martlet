#include "ImageWidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QDebug>

const int lineWidth = 1;

ImageWidget::ImageWidget()
{
    m_bDragMode = false;
    setMouseTracking(true);
}

void ImageWidget::setPixmap(const QString& path)
{
    m_pixmap = QImage(path);
    setMinimumSize(m_pixmap.size());
    m_rect = QRect();
    update();
}

void ImageWidget::savePixmap(const QString& path)
{
    qDebug() << "Saving pixmap rect" << m_rect;
    if ((!path.isEmpty()) && (!m_rect.isNull())) {
        qDebug("Saving as '%s'", qPrintable(path));
        QImage pm = m_pixmap.copy(m_rect);
        pm.save(path,"PNG");
    }
}

void ImageWidget::autoSelect()
{
    QRect targetRect(m_rect);
    bool finished = false;
    while (!finished) {
        finished = true;
        
        /////////////////////////////////////////////////////////////////
        //////////////// TOP ////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////
        
        int lineup = targetRect.top()-1;
        bool allTransparent = true;
        for (int i = targetRect.left(); i<=targetRect.right(); ++i) {
            if (qAlpha(m_pixmap.pixel(i,lineup)) > 0){
                allTransparent = false;
                break;
            }
        }
        if (!allTransparent) {
            targetRect.setTop(lineup);
            finished = false;
        }
        
        /////////////////////////////////////////////////////////////////
        //////////////// BOTTOM //////////////////////////////////////////
        /////////////////////////////////////////////////////////////////
        
        lineup = targetRect.bottom()+1;
        allTransparent = true;
        for (int i = targetRect.left(); i<=targetRect.right(); ++i) {
            if (qAlpha(m_pixmap.pixel(i,lineup)) > 0){
                allTransparent = false;
                break;
            }
        }
        if (!allTransparent) {
            targetRect.setBottom(lineup);
            finished = false;
        }

        /////////////////////////////////////////////////////////////////
        //////////////// LEFT ///////////////////////////////////////////
        /////////////////////////////////////////////////////////////////
        
        lineup = targetRect.left()-1;
        allTransparent = true;
        for (int i = targetRect.top(); i<=targetRect.bottom(); ++i) {
            if (qAlpha(m_pixmap.pixel(lineup,i)) > 0){
                allTransparent = false;
                break;
            }
        }
        if (!allTransparent) {
            targetRect.setLeft(lineup);
            finished = false;
        }

        /////////////////////////////////////////////////////////////////
        //////////////// RIGHT //////////////////////////////////////////
        /////////////////////////////////////////////////////////////////
        
        lineup = targetRect.right()+1;
        allTransparent = true;
        for (int i = targetRect.top(); i<=targetRect.bottom(); ++i) {
            if (qAlpha(m_pixmap.pixel(lineup,i)) > 0){
                allTransparent = false;
                break;
            }
        }
        if (!allTransparent) {
            targetRect.setRight(lineup);
            finished = false;
        }
    }
    m_rect = targetRect;
    update();
}

void ImageWidget::paintEvent( QPaintEvent * /*event*/ )
{
    QPainter painter(this);
    painter.drawImage(0,0, m_pixmap);
    if (!m_rect.isNull()) {
        painter.drawRect(m_rect);
    }
    painter.end();
//    qDebug("Paint Event");
}

void ImageWidget::mouseMoveEvent ( QMouseEvent * event )
{
    if (m_bDragMode) {
        QRect old = m_rect;
        m_rect.setBottomRight(event->pos());
//        qDebug("Move event %d %d", event->pos().x(), event->pos().y());
        repaint(old.united(m_rect).adjusted(0,0, lineWidth, lineWidth));
    }
}

void ImageWidget::mousePressEvent ( QMouseEvent * event )
{
    m_bDragMode = true;
    repaint();
    m_rect = QRect(event->pos(), QSize(1,1));
}

void ImageWidget::mouseReleaseEvent ( QMouseEvent * /*event*/ )
{
    m_bDragMode = false;
//    m_rect = QRect();
//    repaint();
//    update();
}





