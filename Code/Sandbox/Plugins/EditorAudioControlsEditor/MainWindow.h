// Copyright 2001-2018 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include "Common.h"
#include <EditorFramework/Editor.h>
#include <IEditor.h>
#include <CrySystem/ISystem.h>

class QAction;
class QLabel;
class QToolBar;
class QVBoxLayout;

namespace ACE
{
class CSystemControlsWidget;
class CPropertiesWidget;
class CMiddlewareDataWidget;
class CAsset;
class CControl;
class CFileMonitorSystem;
class CFileMonitorMiddleware;

class CMainWindow final : public CDockableEditor, public IEditorNotifyListener, public ISystemEventListener
{
	Q_OBJECT

public:

	CMainWindow(CMainWindow const&) = delete;
	CMainWindow(CMainWindow&&) = delete;
	CMainWindow& operator=(CMainWindow const&) = delete;
	CMainWindow& operator=(CMainWindow&&) = delete;

	CMainWindow();
	virtual ~CMainWindow() override;

	// CDockableEditor
	virtual char const* GetEditorName() const override { return "Audio Controls Editor"; }
	// ~CDockableEditor

	// IEditorNotifyListener
	virtual void OnEditorNotifyEvent(EEditorNotifyEvent event) override;
	// ~IEditorNotifyListener

	// IPane
	virtual IViewPaneClass::EDockingDirection GetDockingDirection() const override { return IViewPaneClass::DOCK_FLOAT; }
	// ~IPane

	void ReloadMiddlewareData();

protected slots:

	void OnSystemControlsWidgetDestruction(QObject* const pObject);
	void OnPropertiesWidgetDestruction(QObject* const pObject);
	void OnMiddlewareDataWidgetDestruction(QObject* const pObject);

private slots:

	void OnPreferencesDialog();

private:

	// ISystemEventListener
	virtual void OnSystemEvent(ESystemEvent event, UINT_PTR wparam, UINT_PTR lparam) override;
	// ~ISystemEventListener

	// QWidget
	virtual void keyPressEvent(QKeyEvent* pEvent) override;
	virtual void closeEvent(QCloseEvent* pEvent) override;
	// ~QWidget

	// CEditor
	virtual void CreateDefaultLayout(CDockableContainer* pSender) override;
	virtual bool CanQuit(std::vector<string>& unsavedChanges) override;
	// ~CEditor

	void                   InitMenuBar();
	void                   InitToolbar(QVBoxLayout* const pWindowLayout);
	void                   UpdateImplLabel();
	void                   RegisterWidgets();
	void                   Reload(bool const hasImplChanged = false);
	void                   Save();
	void                   SaveBeforeImplementationChange();
	void                   CheckErrorMask();
	void                   UpdateAudioSystemData();
	void                   ReloadSystemData();
	void                   RefreshAudioSystem();
	bool                   TryClose();

	Assets                 GetSelectedAssets();

	CSystemControlsWidget* CreateSystemControlsWidget();
	CPropertiesWidget*     CreatePropertiesWidget();
	CMiddlewareDataWidget* CreateMiddlewareDataWidget();

	QToolBar*                 m_pToolBar;
	QAction*                  m_pSaveAction;
	QLabel* const             m_pImplNameLabel;
	CFileMonitorSystem* const m_pMonitorSystem;
	bool                      m_isModified;
	bool                      m_isReloading;
};
} // namespace ACE
