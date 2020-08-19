/**
 * HeliRig Menu
 * 
 * A GUI HeliRig Menu for the UC Online HeliRigs
 * 
 * Author: Jos Craw
 */


function clearMenu() {
    $('#menu-list').html("");
}

function changeMenuTitle(name) {
    $('#menu-title').html(`<li class="menu-tile">${name}</li>`);
}

function addMenuItem(name, selected, label, submenu) {
    let menuIcon = 'mif-file-code'
    if (submenu === true) {
        menuIcon = 'mif-folder';
    }
    if (label !== '') {
        if (selected === true) {
            $('#menu-list').append(`<li><a href='#'><span class="mif-arrow-right"></span>${name} ${label}</a></li>`)
        } else {
            $('#menu-list').append(`<li><a href='#'><span class="${menuIcon}"></span>${name} ${label}</a></li>`)
        }
    } else {
        if (selected === true) {
            $('#menu-list').append(`<li><a href='#'><span class="mif-arrow-right"></span> ${name}</a></li>`)
        } else {
            $('#menu-list').append(`<li><a href='#'><span class="${menuIcon}"></span> ${name}</a></li>`)
        }
    }
}