/**
 * HeliRig Menu
 * 
 * A GUI HeliRig Menu for the UC Online HeliRigs
 * 
 * Author: Jos Craw
 */


function clearMenu() {
    $('#operationpanelcontents').html("<b id='menu-title'></b><ul id='menu-list'></ul>");
}

function changeMenuTitle(name) {
    $('#menu-title').text(name);
}

function addMenuItem(name, selected, label) {
    if (label !== '') {
        if (selected === true) {
            $('#menu-list').append(`<li>>${name} (${label})</li>`)
        } else {
            $('#menu-list').append(`<li>${name} (${label})</li>`)
        }
    } else {
        if (selected === true) {
            $('#menu-list').append(`<li>>${name}</li>`)
        } else {
            $('#menu-list').append(`<li>${name}</li>`)
        }
    }
}