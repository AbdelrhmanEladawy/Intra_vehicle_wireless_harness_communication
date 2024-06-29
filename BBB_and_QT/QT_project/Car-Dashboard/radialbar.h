#ifndef RADIALBAR_H
#define RADIALBAR_H

#include <QQuickPaintedItem>

/**
 * @brief The RadialBar class provides a customizable radial progress bar.
 *
 * This class allows for the creation and customization of a radial progress bar,
 * including properties such as size, angles, colors, and text.
 */
class RadialBar : public QQuickPaintedItem
{
    Q_OBJECT

    // Properties for QML integration with getters, setters, and notifications
    Q_PROPERTY(qreal size READ getSize WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(qreal startAngle READ getStartAngle WRITE setStartAngle NOTIFY startAngleChanged)
    Q_PROPERTY(qreal spanAngle READ getSpanAngle WRITE setSpanAngle NOTIFY spanAngleChanged)
    Q_PROPERTY(qreal minValue READ getMinValue WRITE setMinValue NOTIFY minValueChanged)
    Q_PROPERTY(qreal maxValue READ getMaxValue WRITE setMaxValue NOTIFY maxValueChanged)
    Q_PROPERTY(qreal value READ getValue WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(int dialWidth READ getDialWidth WRITE setDialWidth NOTIFY dialWidthChanged)
    Q_PROPERTY(QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QColor foregroundColor READ getForegroundColor WRITE setForegroundColor NOTIFY foregroundColorChanged)
    Q_PROPERTY(QColor progressColor READ getProgressColor WRITE setProgressColor NOTIFY progressColorChanged)
    Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QString suffixText READ getSuffixText WRITE setSuffixText NOTIFY suffixTextChanged)
    Q_PROPERTY(bool showText READ isShowText WRITE setShowText)
    Q_PROPERTY(Qt::PenCapStyle penStyle READ getPenStyle WRITE setPenStyle NOTIFY penStyleChanged)
    Q_PROPERTY(DialType dialType READ getDialType WRITE setDialType NOTIFY dialTypeChanged)
    Q_PROPERTY(QFont textFont READ getTextFont WRITE setTextFont NOTIFY textFontChanged)

public:
    /**
     * @brief Constructs a RadialBar object.
     *
     * @param parent Pointer to the parent QQuickItem.
     */
    RadialBar(QQuickItem *parent = nullptr);

    /**
     * @brief Paints the radial bar.
     *
     * This function overrides the QQuickPaintedItem's paint method to draw the radial bar.
     *
     * @param painter Pointer to the QPainter used for drawing.
     */
    void paint(QPainter *painter) override;

    /**
     * @brief The DialType enum defines the types of dials.
     */
    enum DialType { FullDial, MinToMax, NoDial };
    Q_ENUM(DialType)

    // Getter methods for properties
    qreal getSize() const { return m_Size; }
    qreal getStartAngle() const { return m_StartAngle; }
    qreal getSpanAngle() const { return m_SpanAngle; }
    qreal getMinValue() const { return m_MinValue; }
    qreal getMaxValue() const { return m_MaxValue; }
    qreal getValue() const { return m_Value; }
    int getDialWidth() const { return m_DialWidth; }
    QColor getBackgroundColor() const { return m_BackgroundColor; }
    QColor getForegroundColor() const { return m_DialColor; }
    QColor getProgressColor() const { return m_ProgressColor; }
    QColor getTextColor() const { return m_TextColor; }
    QString getSuffixText() const { return m_SuffixText; }
    bool isShowText() const { return m_ShowText; }
    Qt::PenCapStyle getPenStyle() const { return m_PenStyle; }
    DialType getDialType() const { return m_DialType; }
    QFont getTextFont() const { return m_TextFont; }

    // Setter methods for properties
    void setSize(qreal size);
    void setStartAngle(qreal angle);
    void setSpanAngle(qreal angle);
    void setMinValue(qreal value);
    void setMaxValue(qreal value);
    void setValue(qreal value);
    void setDialWidth(qreal width);
    void setBackgroundColor(QColor color);
    void setForegroundColor(QColor color);
    void setProgressColor(QColor color);
    void setTextColor(QColor color);
    void setSuffixText(QString text);
    void setShowText(bool show);
    void setPenStyle(Qt::PenCapStyle style);
    void setDialType(DialType type);
    void setTextFont(QFont font);

signals:
    // Signal declarations for property changes
    void sizeChanged();
    void startAngleChanged();
    void spanAngleChanged();
    void minValueChanged();
    void maxValueChanged();
    void valueChanged();
    void dialWidthChanged();
    void backgroundColorChanged();
    void foregroundColorChanged();
    void progressColorChanged();
    void textColorChanged();
    void suffixTextChanged();
    void penStyleChanged();
    void dialTypeChanged();
    void textFontChanged();

private:
    qreal m_Size;
    qreal m_StartAngle;
    qreal m_SpanAngle;
    qreal m_MinValue;
    qreal m_MaxValue;
    qreal m_Value;
    int m_DialWidth;
    QColor m_BackgroundColor;
    QColor m_DialColor;
    QColor m_ProgressColor;
    QColor m_TextColor;
    QString m_SuffixText;
    bool m_ShowText;
    Qt::PenCapStyle m_PenStyle;
    DialType m_DialType;
    QFont m_TextFont;
};

#endif // RADIALBAR_H
