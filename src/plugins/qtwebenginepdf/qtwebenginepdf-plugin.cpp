#include "qtwebenginepdf-plugin.h"
#include <QtWebEngine>
#include <QWebEnginePage>
#include <QWebEngineView>
#include <QPageLayout>
#include <QPageSize>
#include <QApplication>

CQtWebEnginePdfPlugin::CQtWebEnginePdfPlugin()
{
    QApplication* app = qobject_cast<QApplication*>(QApplication::instance());
    if(!app) {
        qFatal("You application must have a QApplication object - QGuiApplication is not enough");
    }
}

CQtWebEnginePdfPlugin::~CQtWebEnginePdfPlugin()
{
}

QList<PluginInterfaceMdQt::ConvertType> CQtWebEnginePdfPlugin::availableConversions()
{
    QList<PluginInterfaceMdQt::ConvertType> supported;
    supported.append({CMarkDownQt::FormatHtmlUtf8, CMarkDownQt::FormatPdfBin});
    return supported;
}

QString CQtWebEnginePdfPlugin::displayName()
{
    return QStringLiteral("qtwebenginepdf");
}

bool CQtWebEnginePdfPlugin::convert(ConvertType convertType, const QByteArray dataIn, QByteArray& dataOut)
{
    bool bSupported = false;
    if(convertType.inFormat==CMarkDownQt::FormatHtmlUtf8 &&
            convertType.outFormat==CMarkDownQt::FormatPdfBin) {
        dataOut = convertToPdf(dataIn);
    }
    return bSupported;
}

QByteArray CQtWebEnginePdfPlugin::convertToPdf(QByteArray strHtmlUtf8)
{
    QByteArray strPdf;
    if(strHtmlUtf8.size() > 0) {
        // yes - we need options for plugins
        QUrl baseUrl = QUrl();
        QMarginsF minMargins;
        minMargins.setLeft(5.0);
        minMargins.setRight(5.0);
        minMargins.setTop(15.0);
        minMargins.setBottom(15.0);
        QPageLayout pageLayout =
                QPageLayout(
                    QPageSize(QPageSize::A4),
                    QPageLayout::Portrait,
                    QMarginsF(),
                    QPageLayout::Millimeter,
                    minMargins);

        QWebEnginePage webPage;
        // load
        webPage.setHtml(strHtmlUtf8, baseUrl);
        bool bLoadOK = false;
        QEventLoop loop;
        connect(&webPage, &QWebEnginePage::loadFinished, [&](bool bOk) {
            bLoadOK = bOk;
            loop.quit();
        });
        loop.exec();

        // -> pdf
        if(bLoadOK) {
            webPage.printToPdf([&](const QByteArray &strPdfCreated) {
                    strPdf = strPdfCreated;
                    loop.quit();
                },
                pageLayout);
            loop.exec();
        }
        else {
            qWarning("PDF export: page was not loaded!");
        }
    }
    return strPdf;
}
