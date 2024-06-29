#include "radialbar.h"
#include <QPainter>

/**
 * @brief Constructs a RadialBar object.
 *
 * Initializes the RadialBar with default values and sets up the item properties.
 *
 * @param parent Pointer to the parent QQuickItem.
 */
RadialBar::RadialBar(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , m_Size(200)
    , m_StartAngle(40)
    , m_SpanAngle(280)
    , m_MinValue(0)
    , m_MaxValue(100)
    , m_Value(50)
    , m_DialWidth(15)
    , m_BackgroundColor(Qt::transparent)
    , m_DialColor(QColor(80, 80, 80))
    , m_ProgressColor(QColor(135, 26, 5))
    , m_TextColor(QColor(0, 0, 0))
    , m_SuffixText("")
    , m_ShowText(true)
    , m_PenStyle(Qt::FlatCap)
    , m_DialType(DialType::MinToMax)
{
    setWidth(200);
    setHeight(200);
    setSmooth(true);
    setAntialiasing(true);
}

/**
 * @brief Paints the RadialBar.
 *
 * This function handles the painting of the radial bar, including the dial,
 * background, progress bar, and text.
 *
 * @param painter Pointer to the QPainter used for drawing.
 */
void RadialBar::paint(QPainter *painter)
{
    double startAngle;
    double spanAngle;
    qreal size = qMin(this->width(), this->height());
    setWidth(size);
    setHeight(size);
    QRectF rect = this->boundingRect();
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen = painter->pen();
    pen.setCapStyle(m_PenStyle);

    startAngle = -90 - m_StartAngle;
    if (FullDial != m_DialType) {
        spanAngle = 0 - m_SpanAngle;
    } else {
        spanAngle = -360;
    }

    // Draw outer dial
    painter->save();
    pen.setWidth(m_DialWidth);
    pen.setColor(m_DialColor);
    painter->setPen(pen);
    qreal offset = m_DialWidth / 2;
    if (m_DialType == MinToMax) {
        painter->drawArc(rect.adjusted(offset, offset, -offset, -offset),
                         startAngle * 16,
                         spanAngle * 16);
    } else if (m_DialType == FullDial) {
        painter->drawArc(rect.adjusted(offset, offset, -offset, -offset), -90 * 16, -360 * 16);
    }
    painter->restore();

    // Draw background
    painter->save();
    painter->setBrush(m_BackgroundColor);
    painter->setPen(m_BackgroundColor);
    qreal inner = offset * 2;
    painter->drawEllipse(rect.adjusted(inner, inner, -inner, -inner));
    painter->restore();

    // Draw progress text with suffix
    painter->save();
    painter->setFont(m_TextFont);
    pen.setColor(m_TextColor);
    painter->setPen(pen);
    if (m_ShowText) {
        painter->drawText(rect.adjusted(offset, offset, -offset, -offset),
                          Qt::AlignCenter,
                          QString::number(m_Value) + m_SuffixText);
    } else {
        painter->drawText(rect.adjusted(offset, offset, -offset, -offset),
                          Qt::AlignCenter,
                          m_SuffixText);
    }
    painter->restore();

    // Draw progress bar
    painter->save();
    pen.setWidth(m_DialWidth);
    pen.setColor(m_ProgressColor);
    qreal valueAngle = ((m_Value - m_MinValue) / (m_MaxValue - m_MinValue))
                       * spanAngle; // Map value to angle range
    painter->setPen(pen);
    painter->drawArc(rect.adjusted(offset, offset, -offset, -offset),
                     startAngle * 16,
                     valueAngle * 16);
    painter->restore();
}

/**
 * @brief Sets the size of the RadialBar.
 *
 * @param size The new size for the RadialBar.
 */
void RadialBar::setSize(qreal size)
{
    if (m_Size == size)
        return;
    m_Size = size;
    emit sizeChanged();
}

/**
 * @brief Sets the start angle of the RadialBar.
 *
 * @param angle The new start angle.
 */
void RadialBar::setStartAngle(qreal angle)
{
    if (m_StartAngle == angle)
        return;
    m_StartAngle = angle;
    emit startAngleChanged();
}

/**
 * @brief Sets the span angle of the RadialBar.
 *
 * @param angle The new span angle.
 */
void RadialBar::setSpanAngle(qreal angle)
{
    if (m_SpanAngle == angle)
        return;
    m_SpanAngle = angle;
    emit spanAngleChanged();
}

/**
 * @brief Sets the minimum value of the RadialBar.
 *
 * @param value The new minimum value.
 */
void RadialBar::setMinValue(qreal value)
{
    if (m_MinValue == value)
        return;
    m_MinValue = value;
    emit minValueChanged();
}

/**
 * @brief Sets the maximum value of the RadialBar.
 *
 * @param value The new maximum value.
 */
void RadialBar::setMaxValue(qreal value)
{
    if (m_MaxValue == value)
        return;
    m_MaxValue = value;
    emit maxValueChanged();
}

/**
 * @brief Sets the current value of the RadialBar.
 *
 * @param value The new value.
 */
void RadialBar::setValue(qreal value)
{
    if (m_Value == value)
        return;
    m_Value = value;
    update(); // Update the RadialBar
    emit valueChanged();
}

/**
 * @brief Sets the width of the dial.
 *
 * @param width The new dial width.
 */
void RadialBar::setDialWidth(qreal width)
{
    if (m_DialWidth == width)
        return;
    m_DialWidth = width;
    emit dialWidthChanged();
}

/**
 * @brief Sets the background color of the RadialBar.
 *
 * @param color The new background color.
 */
void RadialBar::setBackgroundColor(QColor color)
{
    if (m_BackgroundColor == color)
        return;
    m_BackgroundColor = color;
    emit backgroundColorChanged();
}

/**
 * @brief Sets the dial color of the RadialBar.
 *
 * @param color The new dial color.
 */
void RadialBar::setForegroundColor(QColor color)
{
    if (m_DialColor == color)
        return;
    m_DialColor = color;
    emit foregroundColorChanged();
}

/**
 * @brief Sets the progress color of the RadialBar.
 *
 * @param color The new progress color.
 */
void RadialBar::setProgressColor(QColor color)
{
    if (m_ProgressColor == color)
        return;
    m_ProgressColor = color;
    emit progressColorChanged();
}

/**
 * @brief Sets the text color of the RadialBar.
 *
 * @param color The new text color.
 */
void RadialBar::setTextColor(QColor color)
{
    if (m_TextColor == color)
        return;
    m_TextColor = color;
    emit textColorChanged();
}

/**
 * @brief Sets the suffix text of the RadialBar.
 *
 * @param text The new suffix text.
 */
void RadialBar::setSuffixText(QString text)
{
    if (m_SuffixText == text)
        return;
    m_SuffixText = text;
    emit suffixTextChanged();
}

/**
 * @brief Sets whether to show the text on the RadialBar.
 *
 * @param show Boolean indicating whether to show the text.
 */
void RadialBar::setShowText(bool show)
{
    if (m_ShowText == show)
        return;
    m_ShowText = show;
}

/**
 * @brief Sets the pen style of the RadialBar.
 *
 * @param style The new pen style.
 */
void RadialBar::setPenStyle(Qt::PenCapStyle style)
{
    if (m_PenStyle == style)
        return;
    m_PenStyle = style;
    emit penStyleChanged();
}

/**
 * @brief Sets the dial type of the RadialBar.
 *
 * @param type The new dial type.
 */
void RadialBar::setDialType(RadialBar::DialType type)
{
    if (m_DialType == type)
        return;
    m_DialType = type;
    emit dialTypeChanged();
}

/**
 * @brief Sets the font of the text on the RadialBar.
 *
 * @param font The new text font.
 */
void RadialBar::setTextFont(QFont font)
{
    if (m_TextFont == font)
        return;
    m_TextFont = font;
    emit textFontChanged();
}
