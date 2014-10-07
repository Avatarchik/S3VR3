#include "TutorialBase.h"

class MainWindow;

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QTextEdit;
QT_END_NAMESPACE

class TutorialCustomShading : public TutorialBase, private metaio::IShaderMaterialOnSetConstantsCallback
{
	Q_OBJECT

	public:
		TutorialCustomShading(MainWindow* mainWindow);
		virtual ~TutorialCustomShading();

	protected slots:
		void onApplyShadersButtonClicked();

	protected:
		MainWindow*						m_pMainWindow;

		QLabel*							m_pShaderErrorLabel;
		QTextEdit*						m_pVertexShaderEdit;
		QTextEdit*						m_pFragmentShaderEdit;
		QPushButton*					m_pApplyShadersButton;

		metaio::IGeometry*				m_pModel;

		void addGUI();

		virtual void loadContent() override;

		virtual void onSetShaderMaterialConstants(const metaio::stlcompat::String& name, void* extra,
			metaio::IShaderMaterialSetConstantsService* constantsService) override;

		bool saveShaders();
};