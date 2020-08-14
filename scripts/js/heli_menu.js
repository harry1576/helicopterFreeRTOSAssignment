/**
 * HeliRig Menu
 * 
 * A GUI HeliRig Menu for the UC Online HeliRigs
 * 
 * Author: Jos Craw
 */

function clearSerialTerminal() {
    $('.menu-element').forEach((element) => {
        element.remove();
    });
}

function updateMenuItems() {
    $('#operationpanelcontents').html("");
    $('#operationpanelcontents').html("<div class='list-group' id='menu-list'></div>");
    $('#menu-list').html("");
    let i = 0;
    $('.menu-element').forEach(element => {
        let selected = false;
        if (element.attr("sel") === "true") {
            selected = true;
            selected_index = i;
        }
        let name = element.attr('name');
        if (selected === true) {
            $('#menu-list').append(`<a href="#" class="list-group-item">${name}</a>`)
        } else {
            $('#menu-list').append(`<a href="#" class="list-group-item active">${name}</a>`)
        }
        i++;
    });
};