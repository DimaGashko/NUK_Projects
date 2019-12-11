/*!
 * Vanilla.js fade* functions
 * For correct work you MUST add "transition: opacity..." to your element
 * Element hiding based on "display: none" property
 * (if you don't want "display: none" you may not need js for it)
 */

export function fadeIn(elem, displayType = 'block') {
    if (!elem || !isHide(elem)) return;

    elem.style.display = displayType;
    elem.style.opacity = 0;

    setTimeout(() => { 
        elem.style.opacity = '';
    }, 20);
}

export function fadeOut(elem) {
    return new Promise((resolve, reject) => {
        if (!elem || isHide(elem)) {
            resolve();
            return;
        };

        elem.style.opacity = 0;

        elem.addEventListener('transitionend', function hide() {
            elem.style.display = 'none';
            elem.removeEventListener('transitionend', hide);
            resolve();
        });
    });
}

export function fadeToggle(elem, displayType = 'block') {
    return new Promise((resolve, reject) => {
        if (!elem || isHide(elem)) {
            fadeIn(elem, displayType);
            resolve();
        } else {
            fadeOut(elem).then(() =>resolve());
        }
    });
}

function isHide(elem) {
    return getComputedStyle(elem).display == 'none';
}