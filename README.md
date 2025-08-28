**A tool for helping Edit Falcon BMS User.cfg**

<img width="694" height="493" alt="image" src="https://github.com/user-attachments/assets/2ea145c3-eefb-4293-b2d8-7bb8a73bca6e" />

<img width="694" height="493" alt="image" src="https://github.com/user-attachments/assets/191e9d62-2942-4890-8276-3af965d2a45d" />

## Localization

.cfg.json files in /Localization is for localization support, change it to translate the discription of the options (internationalization W.I.P)

## Custom Options

Create a folder named **/Custom json/** in the software root directory. Add a ** (any name).cfg.json** file inside it.

example:

```json
        {
            "key": "g_bInitBUPfromDTC",
            "value": 1, //value can be omitted
            "comment": "If set, the UHF Backup presets will be initialized with the UFC DTC values instead of the usual hardcoded internal values."
        }
```



## Todo-List:
- Value validation
- I18n
- clean the code
- add options
