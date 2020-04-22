(function ($) {
    "use strict";

    var ver = 'simpleGallery-1.0.1';

    function debug(message) {
        if (window.console) {
            console.log(message);
        }
    }

    $.fn.simpleGallery = function (options) {
        var opts = $.extend({}, $.fn.simpleGallery.defaults, options);

        if (this.length <= 0) {
            debug('There are no thumbnails in the gallery');
            return false;
        }

        this.each(function () {
            var img = $('<img>');
            img.src = $(this).attr('rel');
        });

        var init = function () {
            var parent_anchor =  $(this).parents(opts.thumbnail_anchor),
                src = parent_anchor.attr(opts.big_image_attr),
                lens_image = parent_anchor.attr(opts.lens_image_attr);
            var image_container = $(this).parents(opts.gallery_container).find(opts.big_image_container);

            var loading_image = $('<img>', {'src': opts.loading_image});
            image_container.html(loading_image);

            var a = $('<a>').attr('data-lens-image', lens_image).addClass(opts.parent_anchor_class);
            var img = $('<img>').load(function(){
                img.appendTo(a);
                image_container.html(a);
            }).attr('src', src).addClass(opts.big_image_class);

        };

        $(this).on(opts.show_event, init);

        return this;
    };

    $.fn.simpleGallery.ver = function () { return ver; };

    $.fn.simpleGallery.defaults = {
        thumbnail_anchor: '.simpleLens-thumbnail-wrapper',
        big_image_class: 'simpleLens-big-image',
        lens_image_attr: 'data-lens-image',
        big_image_attr: 'data-big-image',
        parent_anchor_class: 'simpleLens-lens-image',
        gallery_container: '.simpleLens-gallery-container',
        big_image_container: '.simpleLens-big-image-container',
        loading_image: '../img/view-slider/loading.gif',
        show_event: 'mouseenter'
    };

})( jQuery );