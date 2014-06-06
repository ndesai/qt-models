import QtQuick 2.2
import QtQuick.Window 2.1
import st.app 1.0 as AppStreet
Window {
    visible: true
    width: 360
    height: 360

    AppStreet.SQLiteDatabase {
        id: _SQLiteDatabase
        readonly: false
        source: "store1.sqlite3"
    }

    ListView {
        id: _ListView
        anchors.fill: parent
        delegate: Item {
            height: 50
            width: ListView.view.width
            Text {
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: modelData.key + " / " + modelData.value
            }
        }
    }

    Rectangle {
        width: parent.width
        height: 100
        MouseArea {
            anchors.fill: parent
            onClicked: {
                _SQLiteDatabase.executeQuery("CREATE TABLE IF NOT EXISTS keystore (key varchar(180), value varchar(180))", function()
                {
                    _SQLiteDatabase.executeQuery("INSERT INTO keystore VALUES ('hellox', 'worldx')", function() { });
                })
            }
        }
        color: "green"
        opacity: 0.25
    }

    Rectangle {
        id: _Rect
        width: 100; height: 100;
        color: "red"
        anchors.centerIn: parent
        SequentialAnimation {
            loops: Animation.Infinite
            running: true
            NumberAnimation {
                target: _Rect; property: "rotation";
                duration: 1000;
                from: 0; to: 360;
            }
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                var o = {
                    //                    query: "CREATE TABLE test1234 (property varchar(128))",
                    query: "SELECT * FROM keystore",
                    fn: function(query, status, results)
                    {
                        console.log("query =", query)
                        console.log("status =", status)
                        console.log(JSON.stringify(results, null, 2))
                        _ListView.model = results;
                    }
                }
                _SQLiteDatabase.executeQuery(o.query, o.fn);
            }
        }
    }
}
