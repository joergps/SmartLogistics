package aero.ltls;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

@Controller
public class SmartLogisticsController {

    /** File name (w/o extension) of the template for the index page. */
    private static final String INDEX_PAGE_FILE_NAME = "index";

    /** Name for the REST parameter "hasItem". */
    private static final String PARAM_NAME_HAS_ITEM = "hasItem";

    /**
     * Map the following REST endpoint to "/".
     *
     * @param status
     * @param model
     * @return a {@link String} that represents the template to be used
     */
    @RequestMapping("/")
    public String index(@RequestParam(value=PARAM_NAME_HAS_ITEM, required=false, defaultValue="false") boolean hasItem, Model model) {
        model.addAttribute(PARAM_NAME_HAS_ITEM, hasItem);
        return INDEX_PAGE_FILE_NAME;
    }

}
