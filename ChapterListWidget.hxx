#ifndef CHAPTERLISTWIDGET_HXX
#define CHAPTERLISTWIDGET_HXX

#include <QWidget>

class FrontCoverOverlay: public QWidget {
  Q_OBJECT

public:
  explicit FrontCoverOverlay(QWidget* p_parent = nullptr);

  void setFrontCover(QPixmap const& p_frontCover);
  void setMangaName(QString const& p_mangaName);
  void setAvailableDownloadCount(int p_availableDownloadCount);
  void setReadProgression(float p_percentageRead);

protected:
  void paintEvent(QPaintEvent *) override;
  void mousePressEvent(QMouseEvent* p_event) override;
  void mouseMoveEvent(QMouseEvent* p_event) override;

signals:
  void downloadRequested();

private:
  int m_availableDownloadCount;
  float m_percentageRead;
  bool m_enteredButton;
  bool m_hasToRepaint;
  QColor m_textButtonColor;
  QString m_mangaName;
  QPixmap m_frontCover;
  QRect m_buttonRect;
};





#include "Utils.h"

class QStandardItem;
class QStandardItemModel;
class QTreeView;
class QLabel;

class ChapterListWidget: public QWidget {
  Q_OBJECT

public:
  enum ChapterListColumns {
    eChapterNameColumn = 0,
    eChapterReadColumn
  };
  enum ChapterDataRole {
    eChapterReadRole = Qt::UserRole
  };

  ChapterListWidget(QWidget* p_parent = nullptr);
  void setReadPercentage(int p_chaptersReadCount, int p_allChaptersCount);
  void setAvailableDownloadCount(const QModelIndex& p_index);

public slots:
  void changeManga(const QModelIndex& p_index);
  void markChapterAsRead(QString const& p_chapterName);

signals:
  void chapterSelected(QModelIndex const& p_chapterIndex);
  void downloadRequested();
  void progressionChanged(int p_remainingChaptersToRead);

protected:
  void updateReadState(QStandardItem* p_stateItem, bool p_isChapterRead);
  QModelIndex getChapterIndex(QModelIndex const& p_index);
  void keyReleaseEvent(QKeyEvent* p_event) override;

private:
  void updateChapters();
  void updateTitle();

private:
  int m_chaptersReadCount;
  int m_allChaptersCount;
  QString m_currentMangaName;
  FrontCoverOverlay* m_frontCover;
  QStandardItemModel* m_chaptersModel;
  QTreeView* m_chaptersView;
  QLabel* m_chaptersTitleLabel;
};

#endif // CHAPTERLISTWIDGET_HXX
