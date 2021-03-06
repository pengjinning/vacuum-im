#ifndef BOOKMARKS_H
#define BOOKMARKS_H

#include <interfaces/ipluginmanager.h>
#include <interfaces/ibookmarks.h>
#include <interfaces/iprivatestorage.h>
#include <interfaces/imainwindow.h>
#include <interfaces/iaccountmanager.h>
#include <interfaces/imultiuserchat.h>
#include <interfaces/ixmppuriqueries.h>
#include <interfaces/iservicediscovery.h>
#include <interfaces/ioptionsmanager.h>
#include <interfaces/irostersmodel.h>
#include <interfaces/irostersview.h>
#include <interfaces/ipresencemanager.h>
#include "editbookmarkdialog.h"
#include "editbookmarksdialog.h"

class Bookmarks :
	public QObject,
	public IPlugin,
	public IBookmarks,
	public IOptionsDialogHolder,
	public IRosterDataHolder,
	public IRostersEditHandler,
	public AdvancedDelegateEditProxy
{
	Q_OBJECT;
	Q_INTERFACES(IPlugin IBookmarks IOptionsDialogHolder IRosterDataHolder IRostersEditHandler);
public:
	Bookmarks();
	~Bookmarks();
	virtual QObject *instance() { return this; }
	//IPlugin
	virtual QUuid pluginUuid() const { return BOOKMARKS_UUID; }
	virtual void pluginInfo(IPluginInfo *APluginInfo);
	virtual bool initConnections(IPluginManager *APluginManager, int &AInitOrder);
	virtual bool initObjects();
	virtual bool initSettings();
	virtual bool startPlugin() { return true; }
	//IOptionsHolder
	virtual QMultiMap<int, IOptionsDialogWidget *> optionsDialogWidgets(const QString &ANodeId, QWidget *AParent);
	//IRosterDataHolder
	virtual QList<int> rosterDataRoles(int AOrder) const;
	virtual QVariant rosterData(int AOrder, const IRosterIndex *AIndex, int ARole) const;
	virtual bool setRosterData(int AOrder, const QVariant &AValue, IRosterIndex *AIndex, int ARole);
	//IRostersEditHandler
	virtual quint32 rosterEditLabel(int AOrder, int ADataRole, const QModelIndex &AIndex) const;
	virtual AdvancedDelegateEditProxy *rosterEditProxy(int AOrder, int ADataRole, const QModelIndex &AIndex);
	//AdvancedDelegateEditProxy
	virtual bool setModelData(const AdvancedItemDelegate *ADelegate, QWidget *AEditor, QAbstractItemModel *AModel, const QModelIndex &AIndex);
	//IBookmarks
	virtual bool isReady(const Jid &AStreamJid) const;
	virtual QList<IBookmark> bookmarks(const Jid &AStreamJid) const;
	virtual bool addBookmark(const Jid &AStreamJid, const IBookmark &ABookmark);
	virtual bool setBookmarks(const Jid &AStreamJid, const QList<IBookmark> &ABookmarks);
	virtual QDialog *showEditBookmarkDialog(IBookmark *ABookmark, QWidget *AParent = NULL);
	virtual QDialog *showEditBookmarksDialog(const Jid &AStreamJid, QWidget *AParent = NULL);
signals:
	void bookmarksOpened(const Jid &AStreamJid);
	void bookmarksClosed(const Jid &AStreamJid);
	void bookmarksChanged(const Jid &AStreamJid);
	//IRosterDataHolder
	void rosterDataChanged(IRosterIndex *AIndex, int ARole);
protected:
	void updateRoomIndexes(const Jid &AStreamJid);
	void updateMultiChatWindows(const Jid &AStreamJid);
	void updateMultiChatWindow(IMultiUserChatWindow *AWindow);
	bool isSelectionAccepted(const QList<IRosterIndex *> &ASelected) const;
	void renameBookmark(const Jid &AStreamJid, const IBookmark &ABookmark);
protected:
	QList<IBookmark> loadBookmarksFromXML(const QDomElement &AElement) const;
	void saveBookmarksToXML(QDomElement &AElement, const QList<IBookmark> &ABookmarks) const;
protected:
	void autoStartBookmarks(const Jid &AStreamJid) const;
	void startBookmark(const Jid &AStreamJid, const IBookmark &ABookmark, bool AShowWindow) const;
protected slots:
	void onPrivateStorageOpened(const Jid &AStreamJid);
	void onPrivateDataUpdated(const QString &AId, const Jid &AStreamJid, const QDomElement &AElement);
	void onPrivateDataRemoved(const QString &AId, const Jid &AStreamJid, const QDomElement &AElement);
	void onPrivateDataChanged(const Jid &AStreamJid, const QString &ATagName, const QString &ANamespace);
	void onPrivateStorageClosed(const Jid &AStreamJid);
protected slots:
	void onRostersViewIndexMultiSelection(const QList<IRosterIndex *> &ASelected, bool &AAccepted);
	void onRostersViewIndexContextMenu(const QList<IRosterIndex *> &AIndexes, quint32 ALabelId, Menu *AMenu);
protected slots:
	void onMultiChatPropertiesChanged();
	void onMultiChatWindowToolsMenuAboutToShow();
	void onMultiChatWindowAddBookmarkActionTriggered(bool);
	void onMultiChatWindowEditBookmarkActionTriggered(bool);
	void onMultiChatWindowRemoveBookmarkActionTriggered(bool);
	void onMultiChatWindowCreated(IMultiUserChatWindow *AWindow);
protected slots:
	void onDiscoWindowAddBookmarkActionTriggered(bool);
	void onDiscoIndexContextMenu(const QModelIndex &AIndex, Menu *AMenu);
	void onDiscoItemsWindowCreated(IDiscoItemsWindow *AWindow);
protected slots:
	void onPresenceOpened(IPresence *APresence);
	void onRosterIndexDestroyed(IRosterIndex *AIndex);
	void onStartBookmarkActionTriggered(bool);
	void onEditBookmarkActionTriggered(bool);
	void onChangeBookmarkAutoJoinActionTriggered(bool);
	void onAddBookmarksActionTriggered(bool);
	void onRemoveBookmarksActionTriggered(bool);
	void onEditBookmarksActionTriggered(bool);
	void onEditBookmarksDialogDestroyed();
	void onShortcutActivated(const QString &AId, QWidget *AWidget);
private:
	IPrivateStorage *FPrivateStorage;
	IAccountManager *FAccountManager;
	IMultiUserChatManager *FMultiChatManager;
	IXmppUriQueries *FXmppUriQueries;
	IServiceDiscovery *FDiscovery;
	IOptionsManager *FOptionsManager;
	IRostersModel *FRostersModel;
	IRostersView *FRostersView;
	IPresenceManager *FPresenceManager;
private:
	QMap<Jid, QList<IBookmark> > FBookmarks;
	QMap<Jid, EditBookmarksDialog *> FDialogs;
	QMap<Jid, QMap<IRosterIndex *, IBookmark> > FRoomIndexes;
};

#endif // BOOKMARKS_H
