const playgroundIPages = true;

const pagesConfig = {

    pages: [{
        alias: 'index',
        entry: './src/pages/index/index.js',
        template: './src/pages/index/index.html',
        htmlPath: 'index.html',
    }],

}

if (playgroundIPages) {
    const playground = []

    pagesConfig.pages.push(...playground);
}

module.exports = pagesConfig;