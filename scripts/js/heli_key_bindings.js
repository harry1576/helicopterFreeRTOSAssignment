/*
 * Adding Arrow key bindings to the
 * UC Online HeliRigs
 * 
 * Author: Jos Craw
 */

// UP
$(document).keydown((e) => {
    if (e.keyCode === 38) {
        setIO(0);
    }
})

// DOWN
$(document).keydown((e) => {
    if (e.keyCode === 40) {
        setIO(1);
    }
})

// LEFT
$(document).keydown((e) => {
    if (e.keyCode === 37) {
        setIO(3)
    }
})

// RIGHT
$(document).keydown((e) => {
    if (e.keyCode === 39) {
        setIO(4)
    } 
})