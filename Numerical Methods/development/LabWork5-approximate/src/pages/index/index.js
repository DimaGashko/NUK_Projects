import tmpl from 'lodash/template';
import './index.sass';

import template from './index.template.html';
import data from './data.js';

const $contentSlot = document.querySelector('.content-slot');
$contentSlot.innerHTML = tmpl(template)(data);
