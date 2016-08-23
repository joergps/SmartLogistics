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

	/** State whether the station has an item or not. **/
	private boolean hasItem = false;

    /**
     * Map the following REST endpoint to "/".
     *
     * @param status
     * @param model
     * @return a {@link String} that represents the template to be used
     */
    @RequestMapping("/")
	public String index(@RequestParam(value = PARAM_NAME_HAS_ITEM, required = false) Boolean hasItemCurrently,
			Model model) {
		setHasItem(hasItemCurrently);
		model.addAttribute(PARAM_NAME_HAS_ITEM, isHasItem());
        return INDEX_PAGE_FILE_NAME;
    }

	/**
	 * Getter for {@link #hasItem}.
	 *
	 * @return <code>true</code> if station has an item; <code>false</code>
	 *         otherwise.
	 */
	private boolean isHasItem() {
		return hasItem;
	}

	/**
	 * Setter for {@link #hasItem}.
	 *
	 * @param hasItemCurrently
	 *            a {@link Boolean}; if <code>null</code> then the state is not
	 *            changed
	 */
	private void setHasItem(Boolean hasItemCurrently) {
		if (hasItemCurrently != null) {
			this.hasItem = hasItemCurrently.booleanValue();
		}
	}

}
