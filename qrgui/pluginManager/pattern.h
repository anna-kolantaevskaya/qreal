#pragma once

#include <QtCore/QPointF>

#include "../../qrkernel/ids.h"
#include "pattern.h"

namespace qReal {
class EditorManager;
class GroupNode{
public:
	 GroupNode(QString const &type, QString const &id, const QPointF &position
			  , bool parametr, int quan, int xShift, int yShift);

	QString type;
	QString id;
	QPointF position;
	int quan;
	int xShift;
	int yShift;
	bool parametr;
};

class GroupEdge{
public:
	GroupEdge(QString const &type, QString const &from, QString const &to
			  , bool connectionType, QList<QPoint> points
			  , QList<QPointF> fromPoints, QList<QPointF> toPoints);

	QString type;
	QString from;
	QString to;
	bool connectionType;
	QList<QPoint> points;
	QList<QPointF> fromPoints;
	QList<QPointF> toPoints;
};

class Pattern{
public:
	Pattern();
	Pattern(QString const &editor, QString const &diagram, QString const &name, QString const &inNode, QString const &outNode);
	void setName(QString const &name);
	QString name() const;
	void setEditor(QString const &editor);
	QString editor() const;
	void setDiagram(QString const &diagram);
	QString diagram();
	void addNode(QString const &type, QString const &id, QPointF const &pos
				 , bool parametr, int quan, int xShift, int yShift);
	void addEdge(QString const &type, QString const &from, QString const &to
				 , bool connectionType, QList<QPoint> points
				 , QList<QPointF> fromPoints, QList<QPointF> toPoints);
	QList<GroupNode> nodes() const;
	QList<GroupEdge> edges() const;
	void setInNode(QString const &id);
	void setOutNode(QString const &id);
	QString inNode()const;
	QString outNode()const;
	QPointF size() const;
	void countSize(EditorManager *editorManager);

private:
	QString mGroupName;
	QString mEditor;
	QString mDiagram;
	QList<GroupNode> mNodes;
	QList<GroupEdge> mEdges;
	QString mInNode;
	QString mOutNode;
	QPointF mSize;
};
}
