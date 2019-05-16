const playgroundIPages = true;

const pagesConfig = {

    pages: [{
        alias: 'approximate',
        entry: './src/pages/approximate/approximate.js',
        template: './src/pages/approximate/approximate.html',
        htmlPath: 'approximate/index.html',
    }, {
        alias: 'approximate',
        entry: './src/pages/differential/differential.js',
        template: './src/pages/differential/differential.html',
        htmlPath: 'differential/index.html',
    }],

}

if (playgroundIPages) {
    const playground = []

    pagesConfig.pages.push(...playground);
}

module.exports = pagesConfig;