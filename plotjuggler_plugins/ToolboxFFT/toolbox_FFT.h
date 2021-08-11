#pragma once

#include <QtPlugin>
#include <thread>
#include "PlotJuggler/toolbox_base.h"
#include "PlotJuggler/plotwidget_base.h"

namespace Ui {
class toolbox_fft;
}

class ToolboxFFT : public PJ::ToolboxPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "facontidavide.PlotJuggler3.Toolbox")
  Q_INTERFACES(PJ::ToolboxPlugin)

public:
  ToolboxFFT();

  ~ToolboxFFT() override;

  const char* name() const override
  {
    return "Fast Fourier Transform";
  }

  void init( PJ::PlotDataMapRef& src_data,
            PJ::TransformsMap& transform_map) override;

  std::pair<QWidget*, WidgetType> providedWidget() const override;

  void addCurve(std::string curve_id);
  
public slots:

  bool onShowWidget() override;

private:
  QWidget* _widget;
  Ui::toolbox_fft *ui;

  //bool eventFilter(QObject *obj, QEvent *event) override;

  QString _dragging_curve;

  PJ::PlotWidgetBase* _plot_widget_A = nullptr;
  PJ::PlotWidgetBase* _plot_widget_B = nullptr;

  PJ::PlotDataMapRef* _plot_data = nullptr;
  PJ::TransformsMap* _transforms = nullptr;

  PJ::PlotDataMapRef _local_data;

  void updateCurveFFT(double min, double max);

  std::string _curve_name;

  Range _zoom_range;

  Range _prev_range;

private slots:

  void onDragEnterEvent(QDragEnterEvent* event);
  void onDropEvent(QDropEvent* event);
  void onViewResized(const QRectF& rect);
  void onRadioZoomedToggled(bool checked);
  void onSaveCurve();
};
