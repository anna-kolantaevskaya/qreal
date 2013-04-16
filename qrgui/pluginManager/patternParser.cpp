#include <QDomElement>
#include <QDomDocument>
#include <QtCore/QPointF>

#include "patternParser.h"
#include "../../qrkernel/ids.h"
#include "pattern.h"

using namespace qReal;

PatternParser::PatternParser()
{
}

void PatternParser::loadXml(QString const &xml)
{
	mXml = xml;
	mXml.replace("\\\"", "\"");
	mXml.replace("\\n", "\n");
}

void PatternParser::parseGroups(EditorManager *editorManager, QString const &editor, QString const &diagram)
{
	QDomDocument doc;
	if (mXml.isNull()){
		qDebug() << "ERROR: no xml-file to parse";
		return;
	}
	mEditorManager = editorManager;
	mEditor = editor;
	mDiagram = diagram;
	doc.setContent(mXml);
	QDomElement groups = doc.firstChildElement("groups");
	if (groups.isNull()){
		qDebug() << "ERROR: groups tag not found";
		return;
	}
	for (QDomElement group = groups.firstChildElement("group"); !group.isNull();
		 group = group.nextSiblingElement("group"))
	{
		parseGroup(group);
	}
}

QList<Pattern> PatternParser::getPatterns()
{
	return mPatterns;
}

void PatternParser::parseGroup(QDomElement const &group)
{
	Pattern pattern = Pattern(mEditor, mDiagram,
							  group.attribute("name"), group.attribute("inNode"), group.attribute("outNode"));
	for (QDomElement node = group.firstChildElement("groupNode"); !node.isNull();
		 node = node.nextSiblingElement("groupNode"))
	{
		parseNode(node, pattern);
	}
	for (QDomElement edge = group.firstChildElement("groupEdge"); !edge.isNull();
		 edge = edge.nextSiblingElement("groupEdge"))
	{
		parseEdge(edge, pattern);
	}
	pattern.countSize(mEditorManager);
	mPatterns.operator +=(pattern);
}

void PatternParser::parseNode(QDomElement const &node, Pattern &pattern)
{
	float x = node.attribute("xPosition").toFloat();
	float y = node.attribute("yPosition").toFloat();
	QPointF const pos = QPointF(x,y);
	int quan = node.attribute("quan").toInt();
	bool parametr = (node.attribute("parametrized") == "true") ? true : false;
	pattern.addNode(node.attribute("type"), node.attribute("name"), pos
					, quan, parametr);
}

void PatternParser::parseEdge(QDomElement const &edge, Pattern &pattern)
{
	QList<QPoint> points;
	QList<QPointF> fromPoints;
	QList<QPointF> toPoints;
	for (QDomElement point = edge.firstChildElement("point"); !point.isNull();
		 point = point.nextSiblingElement("point"))
	{
		points.append(QPoint(point.attribute("pointX").toInt(), point.attribute("pointY").toInt()));
	}
	for (QDomElement point = edge.firstChildElement("fromPoint"); !point.isNull();
		 point = point.nextSiblingElement("fromPoint"))
	{
		fromPoints.append(QPoint(point.attribute("pointX").toFloat(), point.attribute("pointY").toFloat()));
	}
	for (QDomElement point = edge.firstChildElement("toPoint"); !point.isNull();
		 point = point.nextSiblingElement("toPoint"))
	{
		toPoints.append(QPoint(point.attribute("pointX").toFloat(), point.attribute("pointY").toFloat()));
	}
	pattern.addEdge(edge.attribute("type"), edge.attribute("from")
					, edge.attribute("to"), edge.attribute("connectionType"), points, fromPoints, toPoints);
}
