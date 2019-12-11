const webpack = require('webpack');
const merge = require('webpack-merge');
const common = require('./webpack.common.js');

const CleanWebpackPlugin = require('clean-webpack-plugin');
const BundleAnalyzerPlugin = require('webpack-bundle-analyzer').BundleAnalyzerPlugin;

module.exports = (env = {}) => {

    const plugins = [
        new webpack.NoEmitOnErrorsPlugin(),
        new CleanWebpackPlugin(),
    ];

    if (env.BUNDLE_ANALYZE) {
        plugins.push(new BundleAnalyzerPlugin());
    }

    return merge(common, {
        mode: 'production',
        devtool: 'none',
        plugins: plugins,
    });
}