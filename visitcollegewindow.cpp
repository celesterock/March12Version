#include "visitcollegewindow.h"
#include "ui_visitcollegewindow.h"
#include "college.h"
#include "qspinbox.h"

/***************************************************************************
 * Window will display the name of the college that is being "visited" along
 *  with a table including the souvenir options, the prices, and the ability to
 *  select the quantity of each souvenir that will be purchased.
 *
 * The "Purchase Button" will save the student's purchase decision and move
 *  on to the next college on the trip.
 * *************************************************************************/
VisitCollegeWindow::VisitCollegeWindow(TripPlanner* trip, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::VisitCollegeWindow), // initializes the UI
    trip(trip)                      // trip pointer will reference the current trip
{
    ui->setupUi(this);

    // Connect the Purchase Button's clicked signal to the purchaseButtonClick slot
    connect(ui->purchaseButton, &QPushButton::clicked, this, &VisitCollegeWindow::purchaseButtonClick);
}

VisitCollegeWindow::~VisitCollegeWindow()
{
    delete ui;
}

/***************************************************************************
 * Fills in the info displayed on the VisitCollegeWindow page.
 *  Uses the function: populateSouvenirTable() to read in the souvenir names
 *  and prices.
***************************************************************************/
void VisitCollegeWindow::setCollege(const College& collegeToVisit) {
    // Sets the college name at the top of the window
    ui->collegeNameLabel->setText(collegeToVisit.getCollegeName());

    // Populates the table with the corresponding souvenirs for the college
    populateSouvenirTable(collegeToVisit);
}

/***************************************************************************
 * Puts the souvenirs & prices into the UI table
***************************************************************************/
void VisitCollegeWindow::populateSouvenirTable(const College& collegeToVisit) {
    // Clear any items that may be left in the table
    ui->souvenirAndPriceTable->clear();

    /* Reset the number of rows (will be custom depending on the number of
     *    souvenirs available at that campus) */
    ui->souvenirAndPriceTable->setRowCount(0);

    // Set the Column Headings
    QStringList headers;
    headers << "Souvenir Name" << "Price ($)" << "Quantity to Purchase";
    ui->souvenirAndPriceTable->setHorizontalHeaderLabels(headers);

    for(const auto& souvenir : collegeToVisit.getSouvenirOptions()) {
        // starting at row 0 and adding a row...
        int currentRow = ui->souvenirAndPriceTable->rowCount();
        ui->souvenirAndPriceTable->insertRow(currentRow);

        // Fill in the souvenir name and price for the current row
        ui->souvenirAndPriceTable->setItem(currentRow, 0, new QTableWidgetItem(souvenir.getName()));
        ui->souvenirAndPriceTable->setItem(currentRow, 1, new QTableWidgetItem(QString::number(souvenir.getPrice())));

        // Adjust the column width to ensure none of the text is cut off
        ui->souvenirAndPriceTable->resizeColumnsToContents();

        /* Adds QSpin Boxes so that there is a min/max amount that a user could purchase of each
         * souvenir type. Students can purchase 0 - 5 of EACH TYPE of souvenir */
        QSpinBox* quantitySelector = new QSpinBox();
        quantitySelector -> setMinimum(0);
        quantitySelector -> setMaximum(5);
        ui -> souvenirAndPriceTable -> setCellWidget(currentRow, 2, quantitySelector);
    }
}

/***************************************************************************
 * Retrieves the total quanitity of souvenirs that the user has purchased
 *   and the total price from the UI table.
 * Saves these values in the appropriate node of the trip's linked list.
 * For testing, the values are then printed by accessing the values saved
 *   in the college's node.
 * The window is closed and the next college on the trip is displayed.
***************************************************************************/
void VisitCollegeWindow::purchaseButtonClick() {
    double totalCost = 0.0;
    int totalQuantity = 0;

    /* uses the information entered by the user in the UI Table to determine
     * quantity and price of souvenirs for the individual college */
    for (int rowIndex = 0; rowIndex < ui->souvenirAndPriceTable->rowCount(); rowIndex++) {
        // retrieves the price from the second column of the table
        double price = ui->souvenirAndPriceTable->item(rowIndex, 1)->text().toDouble();

        // retieves the quantity from the QSpinBox
        QSpinBox* quantitySpinBox = qobject_cast<QSpinBox*>(ui->souvenirAndPriceTable->cellWidget(rowIndex, 2));
        int quantity = quantitySpinBox -> value();

        totalQuantity += quantity;
        totalCost += price * quantity;
    }

    // update the struct
    trip->savePurchasesToCollegePurchasesStruct(totalQuantity, totalCost);

    // print to console for testing purposes
    trip->printPurchaseSummary();

    // close the current window because the data has been saved
    this->close();

}
