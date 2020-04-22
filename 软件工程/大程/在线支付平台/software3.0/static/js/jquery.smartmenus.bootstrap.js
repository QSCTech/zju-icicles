/*!
 * SmartMenus jQuery Plugin Bootstrap Addon - v0.3.0 - January 27, 2016
 * http://www.smartmenus.org/
 *
 * Copyright Vasil Dinkov, Vadikom Web Ltd.
 * http://vadikom.com
 *
 * Licensed MIT
 */

(function(factory) {
	if (typeof define === 'function' && define.amd) {
		// AMD
		define(['jquery', 'static/js/jquery.smartmenus'], factory);
	} else if (typeof module === 'object' && typeof module.exports === 'object') {
		// CommonJS
		module.exports = factory(require('jquery'));
	} else {
		// Global jQuery
		factory(jQuery);
	}
} (function($) {

	$.extend($.SmartMenus.Bootstrap = {}, {
		keydownFix: false,
		init: function() {
			// init all navbars that don't have the "data-sm-skip" attribute set
			var $navbars = $('ul.navbar-nav:not([data-sm-skip])');
			$navbars.each(function() {
				var $this = $(this),
					obj = $this.data('smartmenus');
				// if this navbar is not initialized
				if (!obj) {
					$this.smartmenus({

							// these are some good default options that should work for all
							// you can, of course, tweak these as you like
							subMenusSubOffsetX: 2,
							subMenusSubOffsetY: -6,
							subIndicators: false,
							collapsibleShowFunction: null,
							collapsibleHideFunction: null,
							rightToLeftSubMenus: $this.hasClass('navbar-right'),
							bottomToTopSubMenus: $this.closest('.navbar').hasClass('navbar-fixed-bottom')
						})
						.bind({
							// set/unset proper Bootstrap classes for some menu elements
							'show.smapi': function(e, menu) {
								var $menu = $(menu),
									$scrollArrows = $menu.dataSM('scroll-arrows');
								if ($scrollArrows) {
									// they inherit border-color from body, so we can use its background-color too
									$scrollArrows.css('background-color', $(document.body).css('background-color'));
								}
								$menu.parent().addClass('open');
							},
							'hide.smapi': function(e, menu) {
								$(menu).parent().removeClass('open');
							}
						});

					function onInit() {
						// set Bootstrap's "active" class to SmartMenus "current" items (should someone decide to enable markCurrentItem: true)
						$this.find('a.current').parent().addClass('active');
						// remove any Bootstrap required attributes that might cause conflicting issues with the SmartMenus script
						$this.find('a.has-submenu').each(function() {
							var $this = $(this);
							if ($this.is('[data-toggle="dropdown"]')) {
								$this.dataSM('bs-data-toggle-dropdown', true).removeAttr('data-toggle');
							}
							if ($this.is('[role="button"]')) {
								$this.dataSM('bs-role-button', true).removeAttr('role');
							}
						});
					}

					onInit();

					function onBeforeDestroy() {
						$this.find('a.current').parent().removeClass('active');
						$this.find('a.has-submenu').each(function() {
							var $this = $(this);
							if ($this.dataSM('bs-data-toggle-dropdown')) {
								$this.attr('data-toggle', 'dropdown').removeDataSM('bs-data-toggle-dropdown');
							}
							if ($this.dataSM('bs-role-button')) {
								$this.attr('role', 'button').removeDataSM('bs-role-button');
							}
						});
					}

					obj = $this.data('smartmenus');

					// custom "isCollapsible" method for Bootstrap
					obj.isCollapsible = function() {
						return !/^(left|right)$/.test(this.$firstLink.parent().css('float'));
					};

					// custom "refresh" method for Bootstrap
					obj.refresh = function() {
						$.SmartMenus.prototype.refresh.call(this);
						onInit();
						// update collapsible detection
						detectCollapsible(true);
					}

					// custom "destroy" method for Bootstrap
					obj.destroy = function(refresh) {
						onBeforeDestroy();
						$.SmartMenus.prototype.destroy.call(this, refresh);
					}

					// keep Bootstrap's default behavior for parent items when the "data-sm-skip-collapsible-behavior" attribute is set to the ul.navbar-nav
					// i.e. use the whole item area just as a sub menu toggle and don't customize the carets
					if ($this.is('[data-sm-skip-collapsible-behavior]')) {
						$this.bind({
							// click the parent item to toggle the sub menus (and reset deeper levels and other branches on click)
							'click.smapi': function(e, item) {
								if (obj.isCollapsible()) {
									var $item = $(item),
										$sub = $item.parent().dataSM('sub');
									if ($sub && $sub.dataSM('shown-before') && $sub.is(':visible')) {
										obj.itemActivate($item);
										obj.menuHide($sub);
										return false;
									}
								}
							}
						});
					}

					// onresize detect when the navbar becomes collapsible and add it the "sm-collapsible" class
					var winW;
					function detectCollapsible(force) {
						var newW = obj.getViewportWidth();
						if (newW != winW || force) {
							var $carets = $this.find('.caret');
							if (obj.isCollapsible()) {
								$this.addClass('sm-collapsible');
								// set "navbar-toggle" class to carets (so they look like a button) if the "data-sm-skip-collapsible-behavior" attribute is not set to the ul.navbar-nav
								if (!$this.is('[data-sm-skip-collapsible-behavior]')) {
									$carets.addClass('navbar-toggle sub-arrow');
								}
							} else {
								$this.removeClass('sm-collapsible');
								if (!$this.is('[data-sm-skip-collapsible-behavior]')) {
									$carets.removeClass('navbar-toggle sub-arrow');
								}
							}
							winW = newW;
						}
					};
					detectCollapsible();
					$(window).bind('resize.smartmenus' + obj.rootId, detectCollapsible);
				}
			});
			// keydown fix for Bootstrap 3.3.5+ conflict
			if ($navbars.length && !$.SmartMenus.Bootstrap.keydownFix) {
				// unhook BS keydown handler for all dropdowns
				$(document).off('keydown.bs.dropdown.data-api', '.dropdown-menu');
				// restore BS keydown handler for dropdowns that are not inside SmartMenus navbars
				if ($.fn.dropdown && $.fn.dropdown.Constructor) {
					$(document).on('keydown.bs.dropdown.data-api', '.dropdown-menu:not([id^="sm-"])', $.fn.dropdown.Constructor.prototype.keydown);
				}
				$.SmartMenus.Bootstrap.keydownFix = true;
			}
		}
	});

	// init ondomready
	$($.SmartMenus.Bootstrap.init);

	return $;
}));