#pragma once

#include <QtCore/QPointF>

#include "../../qrkernel/ids.h"
#include "pattern.h"

namespace qReal {
class EditorManager;
class GroupNode{
public:
	 GroupNode(QString const &type, QString const &id, const QPointF &position
			  , int quan, bool parametr);

	QString type;
	QString id;
	QPointF position;
	int quan;
	bool parametr;
};

class GroupEdge{
public:
	GroupEdge(QString const &type, QString const &from, QString const &to
			  , const QString &connectionType, QList<QPoint> points);

	QString type;
	QString from;
	QString to;
	QString connectionType;
	QList<QPoint> points;
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
				 , int quan, bool parametr);
	void addEdge(QString const &type, QString const &from, QString const &to
				 , const QString &connectionType, QList<QPoint> points);
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
