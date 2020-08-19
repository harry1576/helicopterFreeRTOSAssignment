/**
 * Heli Redesigner.
 * 
 * This redesignes the HeliRig Page using Metro4 design
 * https://metroui.org.ua/
 * 
 * Author:
 * Jos Craw 
 */

const ribbon_menu = `<nav data-role="ribbonmenu">
<ul class="tabs-holder">
    <li><a href="#section-heli-controls">Heli Controls</a></li>
</ul>

<div class="content-holder">
    <div class="section" id="section-heli-controls">
        <div class="group">

            <div data-role="buttonsGroup" data-cls-active="active">
                <button id='heli-up-button' class="ribbon-button">
                    <span class="icon">
                        <span class="mif-arrow-up"></span>
                    </span>
                    <span class="caption">Up</span>
                </button>
                <button id='heli-down-button' class="ribbon-button">
                    <span class="icon">
                        <span class="mif-arrow-down"></span>
                    </span>
                    <span class="caption">Down</span>
                </button>
                <button id='heli-left-button' class="ribbon-button">
                    <span class="icon">
                        <span class="mif-arrow-left"></span>
                    </span>
                    <span class="caption">Left</span>
                </button>
                <button id='heli-right-button' class="ribbon-button">
                    <span class="icon">
                        <span class="mif-arrow-right"></span>
                    </span>
                    <span class="caption">Right</span>
                </button>
                <button id='heli-switch-button' class="ribbon-button">
                    <span class="icon">
                        <span class="mif-play"></span>
                    </span>
                    <span class="caption">Switch</span>
                </button>
            </div>

            <span class="title">Navigation</span>
        </div>
        <div class="group">

            <div data-role="buttonsGroup">
                <button id='heli-hard-reset-button' class="ribbon-button">
                    <span class="icon">
                        <span class="mif-switch"></span>
                    </span>
                    <span class="caption">Hard Reset</span>
                </button>
                <button id='heli-soft-reset-button' class="ribbon-button">
                    <span class="icon">
                        <span class="mif-replay"></span>
                    </span>
                    <span class="caption">Soft Reset</span>
                </button>
            </div>

            <span class="title">Resets</span>
        </div>
        <div class="group">

            <div data-role="buttonsGroup">
                <button id='heli-leave-button' class="ribbon-button">
                    <span class="icon">
                        <span class="mif-cross"></span>
                    </span>
                    <span class="caption">End Session</span>
                </button>
                <button id='heli-logout-button' class="ribbon-button">
                    <span class="icon">
                        <span class="mif-exit"></span>
                    </span>
                    <span class="caption">Logout</span>
                </button>
            </div>

            <span class="title">Session Control</span>
        </div>
    </div>
</div>
</nav>`

const plotHTMLYaw = `  <div class="p-2" data-role="window" data-title="HeliPlot Yaw" data-resizable="false" data-draggable="true" data-btn-close="false">
                        <div class="window-content p-2">
                            <div id="plot-div-yaw">
                                <canvas id="yawChart" width="400" height="400"></canvas>
                            </div>
                        </div>
                    </div>`

const plotHTMLAlt = `  <div class="p-2" data-role="window" data-title="HeliPlot Altitude" data-resizable="false" data-draggable="true" data-btn-close="false">
                    <div class="window-content p-2">
                        <div id="plot-div-alt">
                            <canvas id="altChart" width="400" height="400"></canvas>
                        </div>
                    </div>
                </div>`

const timeRemaining = `<div class="icon-box border bd-default" style="margin-left: 20%; margin-right: 20%; margin-top: 30px;">
                            <div class="icon bg-cyan fg-white"><span class="mif-alarm"></span></div>
                            <div class="content p-4">
                                <div class="text-upper">Time Remaining:</div>
                                <div id="sessionremainingtime" class="text-upper text-bold text-lead"><span class="hour"></span>:<span class="min"></span>:<span class="sec"></span></div>
                            </div>
                        </div>`

function redesign_heli(heli_num) {
    console.log(heli_num);
    $('body').html("");

    $('body').append('<audio id="heli-sounds" loop><source src="https://storage.googleapis.com/heli.ucquarantine.net/heli.mp3" type="audio/mpeg"></audio>')
    $('body').append('<div style="width" id="controls"></div>');
    $('body').append('<div id="main-page" style="height: auto;"></div>')
    $('#main-page').append('<div id="helilogpanelcontents" hidden></div>')
    $('#main-page').append(timeRemaining);
    $('body').append(`<div id="feed-container" class="card" style="height: ${$('body').height()-300}px;"></div>`)
    $('#feed-container').append(`<div class="p-2" data-role="window" data-title="HeliView" data-resizable="false" data-draggable="true" data-btn-close="false"><div class="window-content p-2"><img style="max-width: 100%; height: auto;" src="http://132.181.52.${heli_num}:7070/camera1.mjpg" class="center"></div></div>`);
    $('#feed-container').append('<div class="p-2" data-role="window" data-title="Heli Menu" data-draggable="true" data-btn-close="false"><ul class="v-menu" id="menu-list"></ul></div>');
    $('#feed-container').append(plotHTML);
    $('body').append('<script src="https://cdn.jsdelivr.net/npm/chart.js@2.8.0"></script>');
    $('#controls').html(ribbon_menu);

    $('body').append('<div id="custom-footer" class="pos-fixed pos-bottom-center">©Josiah Craw 2020 <a href="mailto:jcr124@uclive.ac.nz">jcr124@uclive.ac.nz</a></div>')

    $("#heli-up-button").click( () => {
        setIO(0);
    });

    
    $("#heli-down-button").click( () => {
        setIO(1);
    });

    $("#heli-left-button").click( () => {
        setIO(5);
    });

    $("#heli-right-button").click( () => {
        setIO(4);
    });

    $("#heli-switch-button").click( () => {
        setIO(2);
    });

    $("#heli-hard-reset-button").click( () => {
        actionCommand('reset');
    });

    $("#heli-soft-reset-button").click( () => {
        setIO(3);
    });

    $("#heli-leave-button").click( () => {
        finishSession();
    })

    $("#heli-logout-button").click( () => {
        finishSession();
    })

    $('body').append('<script src="https://storage.googleapis.com/heli.ucquarantine.net/v0.1.2/heli_plot.js"></script>');

    updateSession();
}

function heliPause() {
    console.log("Pausing Heli sounds")
    document.getElementById("heli-sounds").pause();
}

function heliPlay() {
    console.log("Starting Heli Sounds")
    document.getElementById("heli-sounds").play();
}

const heli_num = $('.contentheader :header').html().slice(-1);

redesign_heli(heli_num);