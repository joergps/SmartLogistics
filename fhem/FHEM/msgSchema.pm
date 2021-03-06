# $Id: msgSchema.pm 9812 2015-11-07 19:26:25Z loredo $
##############################################################################
#
#     msgSchema.pm
#     Schema database for FHEM modules and their messaging options.
#     These commands are being used as default setting for FHEM command 'msg'
#     unless there is an explicit msgCmd* attribute.
#
#     FHEM module authors may request to extend this file
#
#     Copyright by Julian Pawlowski
#     e-mail: julian.pawlowski at gmail.com
#
#     This file is part of fhem.
#
#     Fhem is free software: you can redistribute it and/or modify
#     it under the terms of the GNU General Public License as published by
#     the Free Software Foundation, either version 2 of the License, or
#     (at your option) any later version.
#
#     Fhem is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#     GNU General Public License for more details.
#
#     You should have received a copy of the GNU General Public License
#     along with fhem.  If not, see <http://www.gnu.org/licenses/>.
#
##############################################################################

package msgSchema;

use strict;
use warnings;

# FHEM module schema definitions for messaging commands
my $db = {
  'audio' => {

    'AMAD' => {
      'Normal'    => 'set %DEVICE% ttsMsg %MSG%',
      'ShortPrio' => 'set %DEVICE% ttsMsg %MSGSH%',
      'Short'     => 'set %DEVICE% ttsMsg %MSGSH%',
      'defaultValues' => {
        'ShortPrio' => {
          'MSGSH' => 'Achtung!',
        },
        'Short' => {
          'MSGSH' => 'Hinweis!',
        },
      },
    },

    'SONOSPLAYER' => {
      'Normal'    => 'set %DEVICE% Speak %VOLUME% %LANG% |%TITLE%| %MSG%',
      'ShortPrio' => 'set %DEVICE% Speak %VOLUME% %LANG% |%TITLE%| %MSGSH%',
      'Short'     => 'set %DEVICE% Speak %VOLUME% %LANG% |%TITLE%| %MSGSH%',
      'defaultValues' => {
        'Normal' => {
          'VOLUME' => 38,
          'LANG' => 'de',
        },
        'ShortPrio' => {
          'VOLUME' => 33,
          'LANG' => 'de',
          'MSGSH' => 'Achtung!',
        },
        'Short' => {
          'VOLUME' => 28,
          'LANG' => 'de',
          'MSGSH' => '',
        },
      },
    },

    'Text2Speech' => {
      'Normal'    => 'set %DEVICE% tts %MSG%',
      'ShortPrio' => 'set %DEVICE% tts %MSGSH%',
      'Short'     => 'set %DEVICE% tts %MSGSH%',
      'defaultValues' => {
        'ShortPrio' => {
          'MSGSH' => 'Achtung!',
        },
        'Short' => {
          'MSGSH' => 'Hinweis!',
        },
      },
    },

  },

  'light' => {

    'HUEDevice' => {
      'Normal'  => '{ my $dev=\'%DEVICE%\'; my $state=ReadingsVal($dev,"state","off"); fhem "set $dev blink 2 1"; fhem "sleep 4.25; set $dev:FILTER=state!=$state $state"; }',
      'High'    => '{ my $dev=\'%DEVICE%\'; my $state=ReadingsVal($dev,"state","off"); fhem "set $dev blink 10 1"; fhem "sleep 20.25; set $dev:FILTER=state!=$state $state"; }',
      'Low'     => 'set %DEVICE% alert select',
    },
    
  },

  'mail' => {

    'fhemMsgMail' => {
      'Normal'  => '{ my $dev=\'%DEVICE%\'; my $title=\'%TITLE%\'; my $msg=\'%MSG%\'; system("echo \'$msg\' | /usr/bin/mail -s \'$title\' \'$dev\'"); }',
      'High'    => '{ my $dev=\'%DEVICE%\'; my $title=\'%TITLE%\'; my $msg=\'%MSG%\'; system("echo \'$msg\' | /usr/bin/mail -s \'$title\' \'$dev\'"); }',
      'Low'     => '{ my $dev=\'%DEVICE%\'; my $title=\'%TITLE%\'; my $msg=\'%MSG%\'; system("echo \'$msg\' | /usr/bin/mail -s \'$title\' \'$dev\'"); }',
    },

  },

  'push' => {

    'Fhemapppush' => {
      'Normal'  => 'set %DEVICE% message \'%TITLE%: %MSG%\' %ACTION%',
      'High'    => 'set %DEVICE% message \'%TITLE%: %MSG%\' %ACTION%',
      'Low'     => 'set %DEVICE% message \'%TITLE%: %MSG%\' %ACTION%',
      'defaultValues' => {
        'Normal' => {
          'ACTION'    => '',
        },
        'High' => {
          'ACTION'    => '',
        },
        'Low' => {
          'ACTION'    => '',
        },
      },
    },

    'Jabber' => {
      'Normal'  => 'set %DEVICE% msg %RECIPIENT% %TITLE%: %MSG%',
      'High'    => 'set %DEVICE% msg %RECIPIENT% %TITLE%: %MSG%',
      'Low'     => 'set %DEVICE% msg %RECIPIENT% %TITLE%: %MSG%',
    },

    'Pushbullet' => {
      'Normal'  => 'set %DEVICE% message %MSG% | %TITLE% %RECIPIENT%',
      'High'    => 'set %DEVICE% message %MSG% | %TITLE% %RECIPIENT%',
      'Low'     => 'set %DEVICE% message %MSG% | %TITLE% %RECIPIENT%',
    },

    'PushNotifier' => {
      'Normal'  => 'set %DEVICE% message %TITLE%: %MSG%',
      'High'    => 'set %DEVICE% message %TITLE%: %MSG%',
      'Low'     => 'set %DEVICE% message %TITLE%: %MSG%',
    },

    'Pushover' => {
      'Normal'  => 'set %DEVICE% msg \'%TITLE%\' \'%MSG%\' \'%RECIPIENT%\' %PRIORITY% \'\' %RETRY% %EXPIRE% %URLTITLE% %ACTION%',
      'High'    => 'set %DEVICE% msg \'%TITLE%\' \'%MSG%\' \'%RECIPIENT%\' %PRIORITY% \'\' %RETRY% %EXPIRE% %URLTITLE% %ACTION%',
      'Low'     => 'set %DEVICE% msg \'%TITLE%\' \'%MSG%\' \'%RECIPIENT%\' %PRIORITY% \'\' %RETRY% %EXPIRE% %URLTITLE% %ACTION%',
      'defaultValues' => {
        'Normal' => {
          'RECIPIENT' => '',
          'RETRY'     => '',
          'EXPIRE'    => '',
          'URLTITLE'  => '',
          'ACTION'    => '',
        },
        'High' => {
          'RECIPIENT' => '',
          'RETRY'     => '120',
          'EXPIRE'    => '600',
          'URLTITLE'  => '',
          'ACTION'    => '',
        },
        'Low' => {
          'RECIPIENT' => '',
          'RETRY'     => '',
          'EXPIRE'    => '',
          'URLTITLE'  => '',
          'ACTION'    => '',
        },
      },
    },

    'TelegramBot' => {
      'Normal'  => 'set %DEVICE% message %RECIPIENT% %TITLE%: %MSG%',
      'High'    => 'set %DEVICE% message %RECIPIENT% %TITLE%: %MSG%',
      'Low'     => 'set %DEVICE% message %RECIPIENT% %TITLE%: %MSG%',
      'defaultValues' => {
        'Normal' => {
          'RECIPIENT' => '',
        },
        'High' => {
          'RECIPIENT' => '',
        },
        'Low' => {
          'RECIPIENT' => '',
        },
      },
    },

    'yowsup' => {
      'Normal'  => 'set %DEVICE% send %RECIPIENT% %TITLE%: %MSG%',
      'High'    => 'set %DEVICE% send %RECIPIENT% %TITLE%: %MSG%',
      'Low'     => 'set %DEVICE% send %RECIPIENT% %TITLE%: %MSG%',
    },

  },

  'screen' => {

    'AMAD' => {
      'Normal'  => 'set %DEVICE% screenMsg %TITLE%: %MSG%',
      'High'    => 'set %DEVICE% screenMsg %TITLE%: %MSG%',
      'Low'     => 'set %DEVICE% screenMsg %TITLE%: %MSG%',
    },

    'ENIGMA2' => {
      'Normal'  => 'set %DEVICE% msg %ENIGMA2_TYPE% %TIMEOUT% %MSG%',
      'High'    => 'set %DEVICE% msg %ENIGMA2_TYPE% %TIMEOUT% %MSG%',
      'Low'     => 'set %DEVICE% msg %ENIGMA2_TYPE% %TIMEOUT% %MSG%',
      'defaultValues' => {
        'Normal' => {
          'ENIGMA2_TYPE' => 'info',
          'TIMEOUT'     => 8,
        },
        'High' => {
          'ENIGMA2_TYPE'     => 'attention',
          'TIMEOUT'     => 12,
        },
        'Low' => {
          'ENIGMA2_TYPE'     => 'message',
          'TIMEOUT'     => 8,
        },
      },
    },

    'XBMC' => {
      'Normal'  => '{ my $dev=\'%DEVICE%\'; my $title=\'%TITLE%\'; my $msg=\'%MSG%\'; $timeout=\'%TIMEOUT%\'*1000; fhem "set $dev msg $msg $timeout %XBMC_ICON%"; }',
      'High'    => '{ my $dev=\'%DEVICE%\'; my $title=\'%TITLE%\'; my $msg=\'%MSG%\'; $timeout=\'%TIMEOUT%\'*1000; fhem "set $dev msg $msg $timeout %XBMC_ICON%"; }',
      'Low'     => '{ my $dev=\'%DEVICE%\'; my $title=\'%TITLE%\'; my $msg=\'%MSG%\'; $timeout=\'%TIMEOUT%\'*1000; fhem "set $dev msg $msg $timeout %XBMC_ICON%"; }',
      'defaultValues' => {
        'Normal' => {
          'TIMEOUT'   => 8,
          'XBMC_ICON' => 'info',
        },
        'High' => {
          'TIMEOUT'   => 12,
          'XBMC_ICON' => 'warning',
        },
        'Low' => {
          'TIMEOUT'   => 8,
          'XBMC_ICON' => '',
        },
      },
    },

  },
};

sub get {
  return $db;
}

1;
