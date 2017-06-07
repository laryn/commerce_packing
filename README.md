# Commerce Packing

Drupal Commerce module to define a better packaging algorithm.

This module is a continuation of the work started by jhaskins which was spawned from a [discussion in the Commerce UPS issue queue](https://www.drupal.org/node/1548986) and then [worked on by 2ndmile](https://www.drupal.org/sandbox/2ndmile/2290689).

>This module uses a [packing algorithm found on GitHub](https://github.com/mdeboer/php-laff). The algorithm tries to fit the boxes (products) in a container (package) and then returns a height. This module is 'dumb' in that it just keeps chucking boxes at containers until everything fits, then it returns the package needed (brute force method).

>Right now, it is ugly... but it works, with two caveats:

1. You have to patch the shipping module you are trying to use. (See issue queue for [Commerce UPS](https://www.drupal.org/node/2290705) and [Commerce USPS](https://www.drupal.org/node/2290715) patches; a [patched version of Commerce UPS (7.x-2.x-dev) is also available here](https://github.com/laryn/commerce_ups).)
2. If you have a large number (over 50) products to check, it may time out because it is dumb.

> I want to do a lot more work on refining the code but I need to get a project out the door. I have been using this code in this project for several months during testing and it works. It's just ugly. I also have this working with the Commerce USPS module (see issue queue for patch).

> Feedback welcome, help even more so. Just don't do one thing... don't tell me it's ugly. I already know that!
