#pragma once
#include "GcPl.h"
#include "GcPlPlotProgress.h"
#include "GcPlPlotInfo.h"
#include "GcPlPlotPageInfo.h"
#include "GcPlObject.h"


class GCPL_PORT GcPlPlotReactor : public GcRxObject
{
public:
  // Plot Type
  enum PlotType {
    kPlot,
    kPreview,
    kBackgroundPackaging,
    kBackgroundPlot
  };

  // Notification for begin of plot
  virtual void beginPlot(GcPlPlotProgress* pPlotProgress, GcPlPlotReactor::PlotType type);

  // Notification for beginning of an document
  virtual void beginDocument(GcPlPlotInfo& plotInfo,
    const GCHAR * pDocname,
    long nCopies = 1, bool bPlotToFile = false,
    const GCHAR * pFilename = NULL);

  // Notification for begin page
  virtual void beginPage(GcPlPlotPageInfo& pageInfo, GcPlPlotInfo& plotInfo,
    bool bLastPage);

  // Notification for end page
  virtual void endPage(GcPlPlotProgress::SheetCancelStatus status);

  // Notification for end of an document
  virtual void endDocument(GcPlPlotProgress::PlotCancelStatus status);

  // Notification that plot has ended
  virtual void endPlot(GcPlPlotProgress::PlotCancelStatus status);

  // Notification that plot was cancelled
  virtual void plotCancelled();

  // Notification that page was cancelled
  virtual void pageCancelled();

  // Destructor
  virtual ~GcPlPlotReactor();

protected:
  GcPlPlotReactor(void);

};

