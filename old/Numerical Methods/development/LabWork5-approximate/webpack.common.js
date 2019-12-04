const webpack = require('webpack');
const path = require('path');

const HtmlWebpackPlugin = require('html-webpack-plugin');
const MiniCssExtractPlugin = require("mini-css-extract-plugin");

const autoprefixer = require('autoprefixer');
const cssnano = require('cssnano');

const pagesConfig = require('./pagesConfig');

const entries = (function () {
    const entries = {};

    pagesConfig.pages.forEach((page) => {
        entries[page.alias] = page.entry
    });

    return entries;
}());

const htmlWebpackPlugins = pagesConfig.pages.map((page) => {
    return new HtmlWebpackPlugin({
        template: page.template,
        filename: page.htmlPath,
        chunks: [page.alias],

        favicon: "./src/img/favicon.png",
        minify: {
            collapseWhitespace: true,
            removeComments: true,
        },
    })
});

const plugins = [
    new webpack.HashedModuleIdsPlugin(),
    new MiniCssExtractPlugin({
        filename: "css/[name].[contenthash].css",
    }),
];

plugins.push(...htmlWebpackPlugins);

module.exports = {
    mode: 'development',
    entry: entries,
    output: {
        filename: 'js/[name].[contenthash].js',
        path: path.resolve(__dirname, 'dist'),
        publicPath: '/',
    },
    devServer: {
        //historyApiFallback: true,
    },
    module: {
        rules: [{
            test: /\.html$/,
            use: 'raw-loader',
        }, {
            test: /\.js$/,
            exclude: /node_modules/,
            use: [{
                loader: 'babel-loader',
                options: {
                    presets: ['@babel/preset-env'],
                    plugins: [
                        '@babel/plugin-proposal-class-properties',
                        '@babel/plugin-syntax-dynamic-import',
                    ]
                }
            }],
        }, {
            test: /\.(sass|css)$/,
            sideEffects: true,
            use: [
                MiniCssExtractPlugin.loader,
                'css-loader',
                {
                    loader: 'postcss-loader',
                    options: {
                        plugins: [autoprefixer(), cssnano()],
                        sourceMap: true,
                    }
                },
                'sass-loader?sourceMap=true'
            ]
        },
        {
            test: /\.(gif|png|jpe?g|svg|webp)$/i,
            use: [{
                loader: 'file-loader?outputPath=img',
            }, {
                loader: 'image-webpack-loader',
                options: {
                    mozjpeg: {
                        progressive: true,
                        quality: 65
                    },
                    pngquant: {
                        quality: '65-90',
                        speed: 4
                    },
                },
            }],
        }

        ],
    },
    plugins: plugins,
};