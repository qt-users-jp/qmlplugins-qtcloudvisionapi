/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   QtCloudVisionAPI                                                        *
 *   Copyright (C) 2016 by Tasuku Suzuki <stasuku@gmail.com>                 *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Lesser Public License as          *
 *   published by the Free Software Foundation; either version 2 of the      *
 *   License, or (at your option) any later version.                         *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU Lesser General Public License for more details.                     *
 *                                                                           *
 *   You should have received a copy of the GNU Lesser General Public        *
 *   License along with this program; if not, write to the                   *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

import QtQuick 2.6
import QtQuick.Layouts 1.3
import Qt.labs.controls 1.0

import jp.qtusers.tasuku.cloudvisionapi 0.1

ApplicationWindow {
    id: window
    width: 800
    height: 800
    visible: true
    title: "Cloud Vision API"

    header: ToolBar {
        RowLayout {
            anchors.fill: parent

            TextField {
                id: url
                text: 'https://pbs.twimg.com/media/Ca_YRZuUMAEsbES.jpg'
                placeholderText: "URL"
                Layout.fillWidth: true
            }

            ComboBox {
                id: type
                Layout.fillWidth: true
                model: ListModel {
                    id: typeModel
                    ListElement { text: 'Face' }
                    ListElement { text: 'Landmark' }
                    ListElement { text: 'Logo' }
                    ListElement { text: 'Label' }
                    ListElement { text: 'Text' }
                    ListElement { text: 'SafeSearch' }
                    ListElement { text: 'Suggestion' }
                }
                textRole: 'text'
                currentIndex: 4
            }

            ToolButton {
                id: detect
                label: Label {
                    anchors.centerIn: parent
                    text: 'Detect'
                }
                onClicked: {
                    image.source = ''
                    image.source = url.text
                }
            }
        }
    }

    property int currentIndex: 0
    property ListView currentView: [
        faceView,
        landmarkView,
        logoView,
        labelView,
        textView,
        safeSearchView,
        suggestionView,
    ][currentIndex]
    property var currentModel: [
        faceView.model,
        landmarkView.model,
        logoView.model,
        labelView.model,
        textView.model,
        safeSearchView.model,
        suggestionView.model,
    ][currentIndex]

    RowLayout {
        anchors.fill: parent

        Flickable {
            Layout.fillHeight: true
            Layout.fillWidth: true
            contentWidth: image.width
            contentHeight: image.height
            clip: true
            Image {
                id: image
                onStatusChanged: {
                    if (image.status === Image.Ready) {
                        image.grabToImage(function(result) {
                            window.currentIndex = type.currentIndex
                            var model = window.currentModel
                            model.image = result.image
                            model.detect()
                        })
                    }
                }
            }
        }

        Item {
            Layout.fillHeight: true
            Layout.minimumWidth: 300

            ListView {
                id: faceView
                anchors.fill: parent
                visible: currentView == faceView
                model: FaceDetectionModel {
                    maxResults: 10
                }
                delegate: Label {
                    text: model.likelihood
                }
            }
            ListView {
                id: landmarkView
                anchors.fill: parent
                visible: currentView == landmarkView
                model: LandmarkDetectionModel {
                    maxResults: 10
                }
                delegate: Label {
                    text: model.description
                }
            }
            ListView {
                id: logoView
                anchors.fill: parent
                visible: currentView == logoView
                model: LogoDetectionModel {
                    maxResults: 10
                }
                delegate: Label {
                    text: model.description
                }
            }
            ListView {
                id: labelView
                anchors.fill: parent
                visible: currentView == labelView
                model: LabelDetectionModel {
                    maxResults: 10
                }
                delegate: Label {
                    text: model.description
                }
            }
            ListView {
                id: textView
                anchors.fill: parent
                visible: currentView == textView
                model: TextDetectionModel {
                    maxResults: 10
                }
                delegate: Label {
                    text: model.description
                }
            }
            ListView {
                id: safeSearchView
                anchors.fill: parent
                visible: currentView == safeSearchView
                model: SafeSearchDetectionModel {
                    maxResults: 10
                }
                delegate: Label {
                    text: model.description
                }
            }
            ListView {
                id: suggestionView
                anchors.fill: parent
                visible: currentView == suggestionView
                model: SuggestionDetectionModel {
                    maxResults: 10
                }
                delegate: Label {
                    text: model.description
                }
            }

            BusyIndicator {
                anchors.centerIn: parent
                visible: currentModel.status === FaceDetectionModel.Loading
            }
        }
    }

    Component.onCompleted: image.source = url.text
}
