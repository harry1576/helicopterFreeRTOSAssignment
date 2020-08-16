/**
 * heli_sounds.js
 * Script to add helicopter noises to the HeliRigs
 * 
 * Author:
 * Jos Craw
 */

var audioFile = document.createElement('audio');
audioFile.setAttribute('src', 'https://storage.googleapis.com/heli.ucquarantine.net/heli.mp3');

audioFile.addEventListener('ended', function() {
    this.play();
}, false);

function heliPause() {
    console.log("Pausing Heli sounds")
    audioFile.pause();
}

function heliPlay() {
    console.log("Starting Heli Sounds")
    audioFile.play();
}